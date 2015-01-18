#ifndef EATER_DB_DRIVER_
#define EATER_DB_DRIVER_

#include "eater/common.hpp"
#include <string>
#include <functional>

namespace Eater
{
class DB_Driver
{
   public:
    enum Status {
        OK = 0,
        ERROR = 1,
        BUSY = 5,
        FULL = 13,
        ROW = 100,
        DONE = 101,
        OTHER
    };

   public:
    /**
     * Opens database connection.
     *
     * \param location Location of database to open.
     * \return True if opened, else false.
     */
    virtual bool open(const std::string &location) = 0;

    /**
     * Checks if a table exists in the database.
     *
     * \param tbl_name Name of table to check.
     * \return True if table exists, else false.
     */
    virtual bool tableExists(const std::string &tbl_name) = 0;

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
                             const str_vec &col_types) = 0;

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
    virtual bool select(const std::string &tbl,
                        const std::string &what,
                        const std::string &where,
                        std::function<void()> &func) = 0;

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
    virtual bool select(const std::string &tbl,
                        const std::string &what,
                        std::function<void()> &func) = 0;

    /**
     * Updates an entry.
     *
     * \param in In what table.
     * \param to Update to.
     * \param where Condition for update.
     * \return True if update was sucessfull.
     */
    virtual bool update(const std::string &tbl,
                        const std::string &to,
                        const std::string &where) = 0;

    /**
     * Insert into a table.
     *
     * \param tbl Table to insert into.
     * \param col_names Column names.
     * \param col_values Column values.
     * \return true if insert was successfull.
     */
    virtual bool insert(const std::string &tbl,
                        const std::string &col_names,
                        const std::string &col_values) = 0;

    /**
     * Steps the database.
     *
     * \return DONE if no more tep is needed, else ROW, when data has
     * been returned.
     */
    virtual Status step() = 0;

    /**
     * Gets a integer from column col.
     *
     * \param col Column to check in.
     * \return integer in column col.
     */
    virtual int columnInt(int col) = 0;

    /**
     * Gets a string from column col.
     *
     * \param col Column to check in.
     * \return String in column col.
     */
    virtual std::string columnStr(int col) = 0;

    /**
     * Gets a double from column col.
     *
     * \param col Column to check in.
     * \return Double in column col.
     */
    virtual double columnDouble(int col) = 0;

    /**
     * Get last row ide insertion.
     *
     * \return id of last insertion.
     */
    virtual int getLastInsertRowId() = 0;

    /**
     * Closes the connection to the database.
     */
    virtual void close() = 0;
};

} /* Eater */

#endif /* end of include guard: EATER_DB_DRIVER_ */

