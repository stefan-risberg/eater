#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <sqlite3.h>
#include <memory>
#include <vector>

#include "eater/common.hpp"
#include "eater/db_fooditems.hpp"
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
    std::shared_ptr<DB_FoodItems> food_items;

    static const char *tbl_fooditems;
    static const char *col_id;
    static const char *col_name;
    static const char *col_brand;
    static const char *col_date;
    static const char *col_time;
    static const char *col_kcal;
    static const char *col_proteins;
    static const char *col_carbohydrates;
    static const char *col_fats;
    static const char *col_tags;

   public:
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

