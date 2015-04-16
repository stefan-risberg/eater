#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <string>
#include <exception>
#include "eater/common.hpp"
#include "eater/sqlinterface.hpp"

namespace Eater
{
class FoodItem;
class Tags;
class Tag;

/**
 * Database handeling for eater.
 *
 * Functions inside of Unsafe are as the name implies are unsafe, the same goes fore Safe.
 */
class DB {
 public:
    class BaseException : public std::exception {
     private:
        std::string _msg;

     public:
        explicit BaseException(const std::string &msg);
        virtual const char* what() const throw();
    };

    class NotFound : public BaseException {
     public:
        explicit NotFound(const std::string &msg);
    };

    class ExistsAlready : public BaseException {
     public:
        explicit ExistsAlready(const std::string &msg);
    };

    /**
     * Unsafe database handeling.
     *
     * As the name implies all functions are to be treated as unsafe.
     *
     * An example can be that inserts can and will insert duplicates and if id to the
     * item already exists in the database, breakage will insure.
     */
    class Unsafe {
        friend class DB;
     private:
        Unsafe();
        void init(DB *db);
     public:
        /**
         * Inserts a tag.
         *
         * If tags id is -1 it will be given a new id,
         * else the one it has is used.
         *
         * \param tag Tag to insert.
         */
        void insertTag(Tag *tag);

        /**
         * Insert fooditem.
         *
         * If food item id is 1 it will be given a new one.
         *
         * \param it Item to insert.
         */
        void insertFood(FoodItem *it);

     private:
        DB *_db;

    } unsafe;

    class Safe {
        friend class DB;
     private:
        Safe();
        void init(DB *db);

     public:
        void inserTag(Tag *tag);
        void insertFood(FoodItem *it);

     private:
        DB *_db;
    } safe;


    friend class Safe;
    friend class Unsafe;
 public:


 public:
    /**
     * Connects to a database. Needs to be initialized afterworlds
     *
     * \see init
     * \param location Location of database.
     */
    DB(const std::string &location);

    /**
     * Check if a table exists.
     *
     * \param tbl_name Table name.
     */
    bool tableExists(const std::string &tbl_name);

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
    id_t getLastId(const std::string &tbl,
                   const std::string &col);

    /**** Tag *****************************************************************/

    /**
     * Query if a tag exists by its name.
     *
     * \param tag Name of tag.
     */
    bool tagExists(const std::string &tag);

    /**
     * Query if a tag exists by its id.
     *
     * \param id Id of tag.
     */
    bool tagExists(id_t id);

    /**
     * Gets the tags id by its name.
     *
     * \param tag Name of tag.
     * \throws DBNotFound
     * \return id of tag.
     */
    id_t getTagId(const std::string &tag);

    /**
     * Gets the tags name from its id.
     *
     * \param id Id of tag.
     * \throws DBNotFound
     * \return name of the tag.
     */
    std::string getTagName(id_t id);

    /**
     * Removes a tag.
     *
     * \param id Id of tag to remove.
     */
    void removeTag(id_t id);

    /**
     * Rename tag.
     *
     * The id of tag will be the tag in the database that will be renamed, and
     * the name will be the new name.
     *
     * \param tag Tag to rename.
     */
    void renameTag(const Tag &tag);

    /**** End of tags *********************************************************/

    /**** Fooditem ************************************************************/
    bool foodExists(id_t id);

    /**
     * Searches for a food by its name and brand.
     *
     * \param it Item to search for.
     * \return true if a food item with the same name and brand exists.
     */
    bool foodExists(const FoodItem &it);



 private:
    Session sql;

    std::string col_id        = "id"; //!< Generic id column.
    std::string col_name      = "name"; //!< Genereic name column.

    std::string tbl_fooditems = "food_items";
    std::string col_brand     = "brand";
    std::string col_date_time = "date_time";
    std::string col_kcal      = "kcal";
    std::string col_carbs     = "carbs";
    std::string col_proteins  = "proteins";
    std::string col_fats      = "fats";

    std::string tbl_tags      = "tags";

    std::string tbl_food_tags = "food_tags";
    std::string col_tag_id    = "tag_id";
    std::string col_food_id   = "food_id";
};
} /* Eater */

#endif /* end of include guard: EATER_DB_HPP_ */

