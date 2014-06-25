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

        /**
         * Closes the connection to the database.
         */
        virtual ~Sql();

        /**
         * Opens database connection.
         *
         * \param location Location of database to open.
         * \return True if opened, else false. 
         */
        virtual bool open(const std::string &location);

        /**
         * Checks if a table exists in the database.
         *
         * \param tbl_name Name of table to check.
         * \return True if table exists, else false.
         */
        virtual bool tableExists(const std::string &tbl_name);

        /**
         * Create a table in the database.
         *
         * col_names and col_types has to have same amount of items.
         *
         * \param tbl_name  Table name.
         * \param col_names Names of all columns.
         * \param col_types Types of all columns.
         * \return True if created, false if some error was encountered.   
         */
        virtual bool createTable(const std::string &tbl_name,
                                 const str_vec &col_names,
                                 const str_vec &col_types);

        /**
         * Creates a select statement.
         *
         * After select you need to step the statement.
         *
         * \param what What to select.
         * \param from From what.
         * \param where Exclition statement.   
         * \param func User function. 
         * \return True if select was sucessfull.
         */
        virtual bool select(const std::string &what,
                            const std::string &from,
                            const std::string &where,
                            std::function<void()> &func);
        /**
         * Updates an entry.
         *
         * \param in In what table.
         * \param to Update to.
         * \param where Condition for update.
         * \return True if update was sucessfull.
         */
        virtual bool update(const std::string &in,
                            const std::string &to,
                            const std::string &where);

        /**
         * Steps the database.
         *
         * \return DONE if no more steps is needed, else ROW, when data has
         * been returned.
         */
        virtual DB_Driver::Status step();


        virtual int column_int(int col);
        virtual std::string column_str(int col);
        virtual double column_double(int col);

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

    private:
        sqlite3_stmt *st = nullptr;
        shared_sqlite3 sql_db;
    };

} /* Eater */ 

#endif /* end of include guard: EATER_SQL_HPP_ */

