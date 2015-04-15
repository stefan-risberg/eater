#include "eater/db.hpp"
#include <exception>
#include "format.h"
#include "eater/tags.hpp"
#include "eater/fooditem.hpp"

namespace Eater
{


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

    return true;
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

bool DB::tagsExists(const Tags &tags)
{
    for (auto it = tags.begin(); it != tags.end(); it++) {
        if (!tagExists(*it)) {
            return false;
        }
    }
    return true;
}

void DB::insertTag(const std::string &tag)
{
    fmt::Writer q;
    q.Format("insert into {} ({}) values ('{}');")
        << tbl_tags
        << col_name
        << tag;

    try {
        sql << q.str();
    } catch (const std::exception &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to insert a tag. Reason: " << e.what());
    }
}

void DB::insertTags(const Tags &tags) {
    for (auto it = tags.begin(); it != tags.end(); it++) {
        insertTag(*it);
    }
}

} /* Eater */

