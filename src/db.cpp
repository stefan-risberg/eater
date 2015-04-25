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

  try {
      food_tags_table.init(_sql);
  } catch (std::exception const &e) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to initialize table: "
                   << E_MAGENTA(food_tags_table.name()) << ".");
        LOGG_ERROR("Reason: " << e.what());
        return false;
  }

    return true;
}


} /* eater */

