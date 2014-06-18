#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <sqlite3.h>
#include <memory>
#include <vector>

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

        static const char * tlb_fooditems;
        static const char * col_id;
        static const char * col_name;
        static const char * col_brand;
        static const char * col_date;
        static const char * col_time;
        static const char * col_kcal;
        static const char * col_proteins;
        static const char * col_carbohydrates;
        static const char * col_fats;
        static const char * col_tags;

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

        /**
         * Creates a table on the database if it does not exist.
         *
         * Will not check if table already exists, if it does, undefined
         * behavior.
         *
         * \param db Database to create on.
         * \param tbl_name Name of new table.
         * \param col_name Vector of column names.
         * \param col_type Column type.
         * \return True if creation of the table was successfull. Otherwise
         * false.    
         */
        static bool createTable(shared_sqlite3 &db,
                                const std::string &tbl_name,
                                const std::vector<std::string> &col_name,
                                const std::vector<std::string> &col_type);

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

