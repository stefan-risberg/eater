#include "eater/db.hpp"
#include "format.h"
#include "eater/sql.hpp"

namespace Eater
{

const char *DB::tbl_fooditems = "fooditems";

DB::DB() : food_items(nullptr)
{
}

bool DB::open(const std::string &data_base)
{
    if (db == nullptr) {
        LOGG_MESSAGE("shared db ptr null");
        db = std::shared_ptr<DB_Driver>(new Sql());
    }

    if (!db->open(data_base)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }
    LOGG_MESSAGE("Opened databse: " << data_base);

    if (!init()) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - WHAAAAAY!!!!!!!");

        return false;
    }

    return true;
}

bool DB::init()
{
    if (db == nullptr) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - database pointer is null.");

        return false;
    }

    if (food_items == nullptr) {
        food_items = std::shared_ptr<DB_FoodItems>(new DB_FoodItems(db));
    }

    bool r = food_items->init(tbl_fooditems);

    if (!r) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - faild to initialize table "
                                       << food_items->tableName());
        return false;
    }

    LOGG_MESSAGE("Init was successfull.");

    return true;
}

} /* Eater */
