#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <string>
#include "eater/common.hpp"
#include "eater/sqlinterface.hpp"

namespace Eater
{
class FoodItem;
class Tags;
class Tag;

class DB {
 public:
    DB(const std::string &location);

    bool tableExists(const std::string &tbl_name);
    bool init();

    bool tagExists(const std::string &tag);
    bool tagExists(id_t id);

    /**
     * Inserts a tag and returns its id.
     *
     * \param tag New tag to insert.
     * \return If insertion faild -1 otherwise the id.
     */
    id_t insertTag(const Tag &tag);

    void insertTags(const Tags &tags);

 private:
    Session sql;

    std::string col_id        = "id";
    std::string col_name      = "name";

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

