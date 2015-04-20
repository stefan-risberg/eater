#include "eater/db.hpp"
#include "format.h"
#include "eater/tags.hpp"
#include "eater/fooditem.hpp"

namespace eater
{

db_t::unsafe_t::unsafe_t () :
    _db(nullptr)
{}

void db_t::unsafe_t::init(db_t *db)
{
    _db = db;
}

void db_t::unsafe_t::insert(tag_t *tag)
{
    if (tag->id() == -1) {
        tag->id(_db->get_last_id(_db->tbl_tags, _db->col_id) + 1);
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

void db_t::unsafe_t::insert(food_item_t *it)
{
    if (it->id() == -1) {
        it->id(_db->get_last_id(_db->tbl_fooditems, _db->col_id) + 1);
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
        << it->ts.to_str()
        << it->name()
        << it->brand()
        << it->mn.calories()
        << it->mn.carbohydrates()
        << it->mn.proteins()
        << it->mn.fats();

    _db->sql << q.str();
}

db_t::safe_t::safe_t() :
    _db(nullptr)
{}

void db_t::safe_t::init(db_t *db)
{
    _db = db;
}

void db_t::safe_t::insert(tag_t *tag)
{
    if (tag->id() == -1) {
        if (_db->tag_exists(tag->name())) {
            throw exists_already("The tag " + tag->name() + " already exists.");
        }
    } else {
        if(_db->tag_exists(tag->id())) {
            throw exists_already("A tag with id: "
                                + std::to_string(tag->id())
                                + " exists already.");
        }
    }

    _db->unsafe.insert(tag);
}

void db_t::safe_t::insert(food_item_t *it)
{
    if (it->id() == -1) {
        if (_db->food_exists(*it)) {
            throw exists_already("An item with the same name and brand exists "
                                "already.");
        }
    } else {
        if (_db->food_exists(it->id())) {
            throw exists_already("A food item with id: "
                                + std::to_string(it->id())
                                + " exists alreadu.");
        }
    }

    _db->unsafe.insert(it);
}

db_t::db_t(const std::string &location)
{
    try {
        sql.open(location);
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to open database, reason: " << E_MAGENTA(e.what()));
    }

    LOGG_MESSAGE("Opened database: " << E_MAGENTA(location) << ".");
}

bool db_t::table_exists(const std::string &tbl_name)
{
    fmt::Writer w;
    w.Format("select count(*) from sqlite_master where type='table' and name='{}'") << tbl_name;

    auto st = sql.prepare(w.str());

    while(st.step() == sql::ROW) {
        if (st.get_int(0) > 0) {
            return true;
        }
    }

    return false;
}

bool db_t::init()
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

id_t db_t::get_last_id(const std::string &tbl,
                       const std::string &col)
{
    fmt::Writer q;
    q.Format("select {0} from {1} order by {0} desc limit 1;")
        << col
        << tbl;

    auto st = sql.prepare(q.str());

    auto r = st.step();

    if (r == sql::ROW) {
        return st.get_int(0);
    }

    return -1;
}

bool db_t::tag_exists(const std::string &tag)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}='{}';")
        << col_id
        << tbl_tags
        << col_name
        << tag;

    try {
        auto st = sql.prepare(q.str());

        while (st.step() == sql::ROW) {
            if (st.get_int(0) > 0) {
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

bool db_t::tag_exists(id_t id)
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}={};")
        << col_id
        << tbl_tags
        << col_id
        << id;

    try {
        auto st = sql.prepare(q.str());

        while (st.step() == sql::ROW) {
            if (st.get_int(0) > 0) {
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

id_t db_t::get_tag_id(const std::string &tag)
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

        if (r == sql::ROW) {
            return st.get_int(0);
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to get tag: " << tag << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    throw not_found("Did not find tag: " + tag + ".");
}

std::string db_t::get_tag_name(id_t id)
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

        if (r == sql::ROW) {
            return st.get_str(0);
        }
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to get tag: " << std::to_string(id) << ".");
        LOGG_ERROR("Reason: " << e.what());
    }

    throw not_found("Did not find tag: " + std::to_string(id) + ".");
}

void db_t::remove_tag(id_t id)
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

void db_t::rename_tag(const tag_t &tag)
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

bool db_t::food_exists(id_t id)
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

        if (r == sql::ROW) {
            if (st.get_int(0) > 0) {
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

bool db_t::food_exists(const food_item_t &it)
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

        if (r == sql::ROW) {
            if (st.get_int(0) > 0) {
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

} /* eater */

