#ifndef EATER_db_t_HPP_
#define EATER_db_t_HPP_

#include <string>
#include "eater/exception.hpp"
#include "eater/common.hpp"
#include "eater/sqlinterface.hpp"

namespace eater
{
class food_item_t;
class tag_vec;
class tag_t;

/**
 * Database handeling for eater.
 *
 * Functions inside of Unsafe are as the name implies are unsafe, the same goes fore Safe.
 */
class db_t {
 public:
    /**
     * Unsafe database handeling.
     *
     * As the name implies all functions are to be treated as unsafe.
     *
     * An example can be that inserts can and will insert duplicates and if id to the
     * item already exists in the database, breakage will insure.
     */
    class unsafe_t {
        friend class db_t;
     private:
        /**
         * Default constructor.
         */
        unsafe_t();

        /**
         * Initiates the unsafe interface.
         *
         * \param db Database interface.
         */
        void init(db_t *db);
     public:
        /**
         * Inserts a tag.
         *
         * If tags id is -1 it will be given a new id,
         * else the one it has is used.
         *
         * \param tag Tag to insert.
         */
        void insert(tag_t *tag);

        /**
         * Insert fooditem.
         *
         * If food item id is 1 it will be given a new one.
         *
         * \param it Item to insert.
         */
        void insert(food_item_t *it);

     private:
        db_t *_db;

    } unsafe;

    class safe_t {
        friend class db_t;
     private:
        /**
         * Default constructor.
         */
        safe_t();

        /**
         * Initiates the safe interface.
         *
         * \param db Database interface.
         */
        void init(db_t *db);

     public:
        /**
         * Inserts a tag in a data safe way.
         *
         * If the id is anoything else then -1, it will check if the id exists
         * already. Else it will check if the name exists.
         *
         * When id is -1 the inserted id of tag will be set.
         *
         * \param tag Tag to insert.
         */
        void insert(tag_t *tag);

        /**
         * Inserts a food item in a data safe way.o
         *
         * If the id is -1 it will check if the fooditems brand and name
         * combination exists. If inserted the id field of food item is set.
         *
         * If id is set already, it will check if it exists. If it does no
         * insert will be made.
         */
        void insert(food_item_t *it);

     private:
        db_t *_db;
    } safe;


    friend class unsafe_t;
    friend class safe_t;
 public:

 public:
    /**
     * Connects to a database. Needs to be initialized afterworlds
     *
     * \see init
     * \param location Location of database.
     */
    db_t(const str &location);

    /**
     * Check if a table exists.
     *
     * \param tbl_name Table name.
     */
    bool table_exists(const str &tbl_name);

    /**
     * Initializes all tables.
     *
     * \return if something went wrong false is returned.
     */
    bool init();

    /**
     * Returns the last index in tbl on col.
     *
     * \param tbl Table to check on.
     * \param col Column.
     * \return If the column is not a id we get undefined behavior.
     */
    id_t get_last_id(const str &tbl,
                     const str &col);

    /**** Tag *****************************************************************/

    /**
     * Query if a tag exists by its name.
     *
     * \param tag Name of tag.
     */
    bool tag_exists(const str &tag);

    /**
     * Query if a tag exists by its id.
     *
     * \param id Id of tag.
     */
    bool tag_exists(id_t id);

    /**
     * Gets the tags id by its name.
     *
     * \param tag Name of tag.
     * \throws db_tNotFound
     * \return id of tag.
     */
    id_t get_tag_id(const str &tag);

    /**
     * Gets the tags name from its id.
     *
     * \param id Id of tag.
     * \throws db_tNotFound
     * \return name of the tag.
     */
    str get_tag_name(id_t id);

    /**
     * Removes a tag.
     *
     * \param id Id of tag to remove.
     */
    void remove_tag(id_t id);

    /**
     * Rename tag.
     *
     * The id of tag will be the tag in the database that will be renamed, and
     * the name will be the new name.
     *
     * \param tag Tag to rename.
     */
    void rename_tag(const tag_t &tag);

    /**** End of tags *********************************************************/

    /**** Fooditem ************************************************************/
    bool food_exists(id_t id);

    /**
     * Searches for a food by its name and brand.
     *
     * \param it Item to search for.
     * \return true if a food item with the same name and brand exists.
     */
    bool food_exists(const food_item_t &it);



 private:
    session_t sql;

    str col_id        = "id"; //!< Generic id column.
    str col_name      = "name"; //!< Genereic name column.

    str tbl_fooditems = "food_items";
    str col_brand     = "brand";
    str col_date_time = "date_time";
    str col_kcal      = "kcal";
    str col_carbs     = "carbs";
    str col_proteins  = "proteins";
    str col_fats      = "fats";

    str tbl_tags      = "tags";

    str tbl_food_tags = "food_tags";
    str col_tag_id    = "tag_id";
    str col_food_id   = "food_id";
};

typedef std::shared_ptr<db_t> shared_db_t;
typedef std::weak_ptr<db_t> weak_db_t;

} /* eater */

#endif /* end of include guard: EATER_db_t_HPP_ */

