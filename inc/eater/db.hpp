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
        shared_sqlite3 db;

    public:
        std::shared_ptr<DB_FoodItems> food_items;

    public:
        DB();
        bool open(const std::string &data_base);
        void close();

        static bool tableExists(shared_sqlite3 &db,
                                const std::string &table);

        static bool prepare(const shared_sqlite3 &db,
                            const std::string &query,
                            sqlite3_stmt **st,
                            const std::string &call_from);

    private:
        bool init();
    };

} /* Eater */ 
#endif /* end of include guard: EATER_DB_HPP_ */

