#ifndef EATER_SQL_HPP_
#define EATER_SQL_HPP_

#include "eater/common.hpp"
#include "eater/db_driver.hpp"
#include <string>
#include <functional>
#include <utility>

namespace Eater
{
    /**
     * Backend for sql database.
     */
    class Sql : public DB_Driver {
    public:
        /**
         * Does nothing.
         */
        Sql();

        virtual bool open(const std::string &location);

        virtual bool tableExists(const std::string &tbl_name);

        virtual bool createTable(const std::string &tbl_name,
                                 const str_vec &col_names,
                                 const str_vec &col_types);

        bool select(const std::string &what,
                    const std::string &from,
                    const std::string &where);

        virtual DB_Driver::Status step();

    private:
        /**
         * Prepares a statement and runs a user function.
         *
         * The user funciton can/should step the statement.
         *
         * \param querry Querry to prepare.
         * \param var 
         * \return True if the user function was run.
         */
         bool prepare(const std::string &querry,
                      std::function<void()> &func);

    public:
        shared_sqlite3 sql_db;

    private:
        sqlite3_stmt *st = nullptr;
    };

} /* Eater */ 

#endif /* end of include guard: EATER_SQL_HPP_ */

