#include "eater/db_food_items.hpp"

namespace Eater
{
    DB_FoodItems::DB_FoodItems()
    {}

    bool DB_FoodItems::open(const std::string &db)
    {
        auto rc = sqlite3_open(db.c_str(), &(this->db));

        if (rc) {
            LOGG(E_RED("Can't open database: "));
            LOGG(sqlite3_errmsg(this->db));
            LOGG("\n");
            return false;
        } 
        return true;
    }

    bool DB_FoodItems::close()
    {
        sqlite3_close(db);
        return true;
    }

} /* Eater */ 
