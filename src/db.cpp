#include "eater/db.hpp"
#include "format.h"
#include "eater/sql.hpp"

namespace Eater
{
const char *DB::tbl_fooditems = "fooditems";
const char *DB::col_id = "id";
const char *DB::col_name = "name";
const char *DB::col_brand = "brand";
const char *DB::col_date = "date";
const char *DB::col_time = "time";
const char *DB::col_kcal = "kcal";
const char *DB::col_proteins = "proteins";
const char *DB::col_carbohydrates = "carbohydrates";
const char *DB::col_fats = "fats";
const char *DB::col_tags = "tags";

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

    bool r = food_items->init();

    if (!r) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - faild to initialize table "
                                       << tbl_fooditems << ".");
        return false;
    }

    LOGG_MESSAGE("Init was successfull.");

    return true;
}

} /* Eater */
