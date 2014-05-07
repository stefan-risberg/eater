#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <sqlite3.h>
#include <memory>

#include "eater/common.hpp"
#include "eater/db_fooditems.hpp"

namespace Eater
{
    /**
     * Class with access to all database things.
     *
     * If the database has been opened, the connetion is closed when DB is
     * deallocated.
     */
    class DB
    {
    private:
        shared_sqlite3 db; /*< Shared pointer to the database object. */

    public:
        std::shared_ptr<DB_FoodItems> food_items;

    public:
        /**
         * Does nothing.
         */
        DB();

        /**
         * Opens a database connection and makes it ready.
         *
         * It initiates all tables that have to be there if they are not
         * present.
         * 
         * To close connection just deallocate the object.
         *
         * \param data_base Name of new database file.
         * \return True if everything opened sucessfully, else false. 
         */
        bool open(const std::string &data_base);

        /**
         * Check if a tabel exists in a given database.
         *
         * \param db Databse to check in.
         * \param table Name of table.
         * \return True if table exists else false.  
         */
        static bool tableExists(shared_sqlite3 &db,
                                const std::string &table);

        /**
         * Prepares a statement.
         *
         * If there was an error with the preparation, a message will be
         * printed to the terminal.
         *
         * \param db Database to prepare the statement on.
         * \param query Querty to prepare.
         * \param st Statement to be retuned.
         * \return True if prepared, else false. 
         */
        static bool prepare(const shared_sqlite3 &db,
                            const std::string &query,
                            sqlite3_stmt **st);

    private:
        /**
         * Initiates the whole database.
         *
         * \return True if everything when correctly, else false. Read output
         * for explenation if faild.
         */
        bool init();
    };

} /* Eater */ 
#endif /* end of include guard: EATER_DB_HPP_ */

