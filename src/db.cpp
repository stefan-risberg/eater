#include "eater/db.hpp"
#include <exception>
#include "format.h"

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
            << col_tag_id
            << col_food_id;

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

}

