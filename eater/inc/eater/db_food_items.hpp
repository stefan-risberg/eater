#ifndef EATER_DB_FOOD_ITEMS_HPP_
#define EATER_DB_FOOD_ITEMS_HPP_

#include "eater/common.hpp"
#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"
#include "eater/nutrients.hpp"
#include <sqlite3.h>

namespace Eater
{
    typedef std::vector<FoodItem> food_item_vec;

    class DB_FoodItems
    {
    private:
        sqlite3 *db;

    public:
        DB_FoodItems();
        bool open(const std::string &db);
        bool close();

    };
} /* Eater */ 

#endif /* end of include guard: EATER_DB_FOOD_ITEMS_HPP_ */

