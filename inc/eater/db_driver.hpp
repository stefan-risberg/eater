#ifndef EATER_DB_DRIVER_
#define EATER_DB_DRIVER_

#include "eater/common.hpp"
#include <string>

namespace Eater
{
    class DB_Driver {
    public:
        enum Status {
            OK = 0,
            ERROR = 1,
            BUSY = 5,
            FULL = 13,
            ROW = 100,
            DONE = 101
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
         * Steps the database.
         *
         * \return DONE if no more tep is needed, else ROW, when data has
         * been returned.
         */
        virtual Status step() = 0;

    };

} /* Eater */ 

#endif /* end of include guard: EATER_DB_DRIVER_ */

