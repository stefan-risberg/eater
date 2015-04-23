#include "eater/db.hpp"
#include "format.h"
#include "eater/tags.hpp"
#include "eater/fooditem.hpp"

namespace eater
{

db_t::db_t(const std::string &location) :
    _sql(new session_t)
{
    try {
        _sql->open(location);
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to open database, reason: " << E_MAGENTA(e.what()));
    }

    LOGG_MESSAGE("Opened database: " << E_MAGENTA(location) << ".");
}

bool db_t::init()
{
    try {
        food_table.init(_sql);
    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(food_table.name()) << ".");

        LOGG_ERROR("Reason: " << e.what());
        return false;
    }

    try {
        tag_table.init(_sql);

    } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(tag_table.name()) << ".");
        LOGG_ERROR("Reason: " << e.what());
        return false;
    }

//  try {
//      fmt::Writer w;
//      w.Format("create table if not exists {0} ("
//               "{1} integer not null,"
//               "{2} integer not null,"
//               "primary key({1}, {2}),"
//               "foreign key({1}) references {3} ({5}),"
//               "foreign key({2}) references {4} ({5}))")
//          << tbl_food_tags
//          << col_tag_id
//          << col_food_id
//          << tbl_tags
//          << tbl_fooditems
//          << col_id;
//
//      sql << w.str();
//
//      LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_food_tags) << ".");
//  } catch (std::exception const &e) {
//
//  }

    return true;
}


} /* eater */

