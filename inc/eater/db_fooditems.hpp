#ifndef EATER_DB_FOOD_ITEMS_HPP_
#define EATER_DB_FOOD_ITEMS_HPP_

#include "eater/common.hpp"
#include "eater/fooditem.hpp"
#include "eater/table_handler.hpp"
#include "eater/db_driver.hpp"
#include "eater/sql.hpp"

#include <memory>

namespace Eater
{
    class DB_FoodItems : TableHandler
    {
    private:
        static const char * fooditems;
        static const char * id;
        static const char * name;
        static const char * brand;
        static const char * date;
        static const char * time;
        static const char * kcal;
        static const char * proteins;
        static const char * carbohydrates;
        static const char * fats;
        static const char * tags;

    public:
        /**
         * Default constructor.
         *
         * Assigns a valid database object to the food items database.
         *
         * \param sql Database backend. 
         */
        DB_FoodItems(std::shared_ptr<DB_Driver> &db);

        /**
         * Calls close.
         */
        virtual ~DB_FoodItems();

        /**
         * Check if a certain food item exists in database.
         *
         * \param item Item to check if it exists.
         * \return true if it does, else false. 
         */
        bool exists(const id_t item) const;

        /**
         * Check if the item is older then the one in the database.
         *
         * \param item Item to check.
         * \return true if is older, false if it is not odler or if the
         * item was not found in the database. 
         */
        bool old(const FoodItem &item) const;

        /**
         * Updates a given item in the database.
         *
         * Updates the item if it exists, will not check if item is older
         * then the one in the database or if it exists in the database.
         *
         * \param item Item to update.
         */
        void update(const FoodItem &item);

        /**
         * Saves an item.
         *
         * If item id field is anything then -1 saving will fail. The id will be
         * updated for the item if saving was successfull.
         *
         * \param item Item to save.
         * \return false if saving failed, else true.
         */
        bool save(FoodItem &item);

        /**
         * Saves a vector of items.
         *
         * If items id filed is anything else then -1 the item will not be
         * saved. If saved the id filed will be updated for all saved items.
         *
         * \param items Items to save. 
         */
        void save(food_vec &items);

        /**
         * Searches for an item by id in the database.
         *
         * \param id Id to look for.
         * \param item Item will be overwritten if item was found.
         * \return true if found else false.  
         */
        bool find(const id_t id, FoodItem &item) const;

        /**
         * Search for a list of items.
         *
         * Items that aren't found will just be ignored.
         * 
         * \param ids Vector of ids to look for.
         * \return Vector of all the foods that were found.
         */
        food_vec find(const id_vec &ids) const;

        /**
         * Initializes the database.
         *
         * Creates a table with correct values, will not chech if table already exists.
         *
         * \return true if database is ready to use, else false.
         */
        virtual bool init();

        /**
         * Does nothing.
         */
        virtual bool close() { return true; }
    };
} /* Eater */ 

#endif /* end of include guard: EATER_DB_FOOD_ITEMS_HPP_ */

