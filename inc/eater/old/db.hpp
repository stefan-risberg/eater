#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <sqlite3.h>
#include <memory>
#include <vector>

#include "eater/common.hpp"
#include "eater/tbl_fooditems.hpp"
#include "eater/tbl_tags.hpp"
#include "eater/db_driver.hpp"
#include "eater/sql.hpp"

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
    std::shared_ptr<DB_Driver> db; /*< Shared pointer to database backend. */

   public:
    std::shared_ptr<TblFoodItems> food_items;
    std::shared_ptr<TblTags> tags;

   public:
    DB();

    /**
     * Closes all connections to the database.
     */
    virtual ~DB();

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
     * Closes all connection to the database.
     *
     * To use it again, use open first.
     */
    void close();

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

