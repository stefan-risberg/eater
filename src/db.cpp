#include "eater/db.hpp"
#include "format.h"
#include "eater/tags.hpp"
#include "eater/fooditem.hpp"

namespace Eater
{

DB::Unsafe::Unsafe () :
    _db(nullptr)
{}

void DB::Unsafe::init(DB *db)
{
    _db = db;
}

void DB::Unsafe::insertTag(Tag *tag)
{
    if (tag->id() == -1) {
        tag->id(_db->getLastId(_db->tbl_tags, _db->col_id) + 1);
    }

    fmt::Writer q;
    q.Format("insert into {} ({}, {}) values ({}, '{}');")
        << _db->tbl_tags
        << _db->col_id
        << _db->col_name
        << tag->id()
        << tag->name();
    _db->sql << q.str();

}

void DB::Unsafe::insertFood(FoodItem *it)
{
    if (it->id() == -1) {
        it->id(_db->getLastId(_db->tbl_fooditems, _db->col_id) + 1);
    }

    fmt::Writer q;

    q.Format("insert into {} ({}, {}, {}, {}, {}, {}, {}, {}) "
             "values ({}, '{}', '{}', '{}', {}, {}, {}, {});")
        << _db->tbl_fooditems
        << _db->col_id
        << _db->col_date_time
        << _db->col_name
        << _db->col_brand
        << _db->col_kcal
        << _db->col_carbs
        << _db->col_proteins
        << _db->col_fats
        << it->id()
        << it->ts.toString()
        << it->name()
        << it->brand()
        << it->mn.calories()
        << it->mn.carbohydrates()
        << it->mn.proteins()
        << it->mn.fats();

    _db->sql << q.str();
}

DB::Safe::Safe() :
    _db(nullptr)
{}

void DB::Safe::init(DB *db)
{
    _db = db;
}

void DB::Safe::inserTag(Tag *tag)
{
    if (tag->id() == -1) {
        if (_db->tagExists(tag->name())) {
            throw ExistsAlready("The tag " + tag->name() + " already exists.");
        }
    } else {
        if(_db->tagExists(tag->id())) {
            throw ExistsAlready("A tag with id: "
                                + std::to_string(tag->id())
                                + " exists already.");
        }
    }

    _db->unsafe.insertTag(tag);
}

void DB::Safe::insertFood(FoodItem *it)
{
    if (it->id() == -1) {
        if (_db->foodExists(*it)) {
            throw ExistsAlready("An item with the same name and brand exists "
                                "already.");
        }
    } else {
        if (_db->foodExists(it->id())) {
            throw ExistsAlready("A food item with id: "
                                + std::to_string(it->id())
                                + " exists alreadu.");
        }
    }

    _db->unsafe.insertFood(it);
}

DB::DB(const std::string &location)
{
    try {
        sql.open(location);
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to open database, reason: " << E_MAGENTA(e.what()));
    }

    LOGG_MESSAGE("Opened database: " << E_MAGENTA(location) << ".");
}

bool DB::tableExists(const std::string &tbl_name)
{
    fmt::Writer w;
    w.Format("select count(*) from sqlite_master where type='table' and name='{}'") << tbl_name;

    Statement st = sql.prepare(w.str());

    while(st.step() == Sql::ROW) {
        if (st.getInt(0) > 0) {
            return true;
        }
    }

    return false;
}

bool DB::init()
{
    try {
        fmt::Writer w;
        w.Format("create table if not exists {} ("
                 "{} integer primary key,"
                 "{} text not null,"
                 "{} text not null,"
                 "{} text not null,"
                 "{} real not null,"
                 "{} real,"
                 "{} real,"
                 "{} real)")
            << tbl_fooditems
            << col_id
            << col_date_time
            << col_name
            << col_brand
            << col_kcal
            << col_carbs
            << col_proteins
            << col_fats;

        sql << w.str();
        LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_fooditems) << ".");
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(tbl_fooditems) << ".");

        LOGG_ERROR("Reason: " << e.what());
        return false;
    }

    try {
        fmt::Writer w;
        w.Format("create table if not exists {} ("
                 "{} integer primary key,"
                 "{} text not null)")
            << tbl_tags
            << col_id
            << col_name;

        sql << w.str();

        LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_tags) << ".");
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(tbl_tags) << ".");
        LOGG_ERROR("Reason: " << e.what());
        return false;
    }

    try {
        fmt::Writer w;
        w.Format("create table if not exists {0} ("
                 "{1} integer not null,"
                 "{2} integer not null,"
                 "primary key({1}, {2}),"
                 "foreign key({1}) references {3} ({5}),"
                 "foreign key({2}) references {4} ({5}))")
            << tbl_food_tags
            << col_tag_id
            << col_food_id
            << tbl_tags
            << tbl_fooditems
            << col_id;

        sql << w.str();

        LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_food_tags) << ".");
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(tbl_food_tags) << ".");
        LOGG_ERROR("Reason: " << e.what());
        return false;
    }

    unsafe.init(this);
    safe.init(this);

    return true;
}

id_t DB::getLastId(const std::string &tbl,
                   const std::string &col)
{
    fmt::Writer q;
    q.Format("select {0} from {1} order by {0} desc limit 1;")
        << col
        << tbl;

    auto st = sql.prepare(q.str());

    auto r = st.step();

    if (r == Sql::ROW) {
        return st.getInt(0);
    }

    return -1;
}

bool DB::tagExists(const std::string &tag)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}='{}';")
        << col_id
        << tbl_tags
        << col_name
        << tag;

    try {
        auto st = sql.prepare(q.str());

        while (st.step() == Sql::ROW) {
            if (st.getInt(0) > 0) {
                return true;
            }
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to check for a tag: " << tag << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    return false;
}

bool DB::tagExists(id_t id)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}={};")
        << col_id
        << tbl_tags
        << col_id
        << id;

    try {
        auto st = sql.prepare(q.str());

        while (st.step() == Sql::ROW) {
            if (st.getInt(0) > 0) {
                return true;
            }
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to check for a tag: " << id << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    return false;
}

id_t DB::getTagId(const std::string &tag)
{
    fmt::Writer q;
    q.Format("select {} from {} where {}='{}';")
        << col_id
        << tbl_tags
        << col_name
        << tag;
    try {
        auto st = sql.prepare(q.str());
        auto r = st.step();

        if (r == Sql::ROW) {
            return st.getInt(0);
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to get tag: " << tag << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    throw NotFound("Did not find tag: " + tag + ".");
}

std::string DB::getTagName(id_t id)
{
    fmt::Writer q;
    q.Format("select {} from {} where {}={};")
        << col_name
        << tbl_tags
        << col_id
        << id;
    try {
        auto st = sql.prepare(q.str());
        auto r = st.step();

        if (r == Sql::ROW) {
            return st.getStr(0);
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to get tag: " << std::to_string(id) << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    throw NotFound("Did not find tag: " + std::to_string(id) + ".");
}

void DB::removeTag(id_t id)
{
    fmt::Writer q;
    q.Format("delete from {} where {}={};")
        << tbl_tags
        << col_id
        << id;

    try {
        sql << q.str();
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to remove a tag. Reason: " << e.what());
    }
}

void DB::renameTag(const Tag &tag)
{
    fmt::Writer q;
    q.Format("update {} set {}='{}' where {}={};")
        << tbl_tags
        << col_name
        << tag.name()
        << col_id
        << tag.id();

    try {
        sql << q.str();
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to rename a tag. Reason: " << e.what());
    }
}

bool DB::foodExists(id_t id)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}={};")
        << col_id
        << tbl_fooditems
        << col_id
        << id;

    try {
        auto st = sql.prepare(q.str());

        auto r = st.step();

        if (r == Sql::ROW) {
            if (st.getInt(0) > 0) {
                return true;
            }
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to check if food item exists.");
        LOGG_ERROR("Reason: " << e.what());
    }

    return false;
}

bool DB::foodExists(const FoodItem &it)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}='{}' and {}='{}';")
        << col_id
        << tbl_fooditems
        << col_name
        << it.name()
        << col_brand
        << it.brand();

    try {
        auto st = sql.prepare(q.str());

        auto r = st.step();

        if (r == Sql::ROW) {
            if (st.getInt(0) > 0) {
                return true;
            }
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to check if food item exists.");
        LOGG_ERROR("Reason: " << e.what());
    }

    return false;
}

} /* Eater */

