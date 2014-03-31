#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <sqlite3.h>
#include <memory>

#include "eater/common.hpp"
#include "eater/db_fooditems.hpp"

namespace Eater
{
    class DB
    {
    private:
        std::shared_ptr<sqlite3> db;

    public:
        std::shared_ptr<DB_FoodItems> food_items;

    public:
        DB();
        bool open(const std::string &data_base);
        void close();

    private:
        bool init();
        bool tableExists(const std::string &table) const;
    };

} /* Eater */ 
#endif /* end of include guard: EATER_DB_HPP_ */

