#ifndef EATER_SQL_HPP_
#define EATER_SQL_HPP_

#include "eater/common.hpp"
#include "eater/db_driver.hpp"
#include <string>
#include <functional>
#include <utility>
#include <stdint.h>

namespace Eater
{
/**
 * Backend for sql database.
 */
class Sql : public DB_Driver
{
   public:
    /**
     * Opens database connection.
     *
     * \param location Location of database to open.
     * \return True if opened, else false.
     */
    bool open(const std::string &location);

    /**
     * Checks if a table exists in the database.
     *
     * \param tbl_name Name of table to check.
     * \return True if table exists, else false.
     */
    bool tableExists(const std::string &tbl_name);

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
    bool createTable(const std::string &tbl_name,
                     const str_vec &col_names,
                     const str_vec &col_types);

    /**
     * Creates a select statement.
     *
     * After select you need to step the statement.
     *
     * \param tbl What table to select from.
     * \param what What to select.
     * \param where Exclition statement.
     * \param func User function.
     * \return True if select was sucessfull.
     */
    bool select(const std::string &tbl,
                const std::string &what,
                const std::string &where,
                std::function<void()> &func);

    /**
     * Creates a select statment.
     *
     * Stepping have to be done in func.
     *
     * \param tbl Table to select from.
     * \param what What to select.
     * \param func User functino to run on prepared statement.
     * \return true if everything whent good. Else false.
     */
    bool select(const std::string &tbl,
                const std::string &what,
                std::function<void()> &func);
    /**
     * Updates an entry.
     *
     * \param in In what table.
     * \param to Update to.
     * \param where Condition for update.
     * \return True if update was sucessfull.
     */
    bool update(const std::string &tbl,
                const std::string &to,
                const std::string &where);

    /**
     * Insert into a table.
     *
     * \param tbl Table to insert into.
     * \param col_names Column names.
     * \param col_values Column values.
     * \return true if insert was successfull.
     */
    bool insert(const std::string &tbl,
                const std::string &col_names,
                const std::string &col_values);
    /**
     * Steps the database.
     *
     * \return DONE if no more steps is needed, else ROW, when data has
     * been returned.
     */
    DB_Driver::Status step();

    int columnInt(int col);
    std::string columnStr(int col);
    double columnDouble(int col);
    int getLastInsertRowId();

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
    bool prepare(const std::string &querry, const std::function<void()> &func);

    /**
     * Returns last inserted id.
     *
     * Needs to be run before statement is dealocated.
     *
     * \return Id integer of last insertion.
     */

   private:
    sqlite3_stmt *st = nullptr;
    shared_sqlite3 sql_db;
};

} /* Eater */

#endif /* end of include guard: EATER_SQL_HPP_ */

