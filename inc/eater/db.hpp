#ifndef EATER_DB_HPP_
#define EATER_DB_HPP_

#include <string>
#include "eater/common.hpp"
#include <soci.h>
#include <sqlite3/soci-sqlite3.h>
#include <fstream>

namespace Eater
{
class DB {
 public:
    DB(const std::string &location);

    bool tableExists(const std::string &tbl_name);
    bool init();
    ~DB();

 private:
    soci::session sql;

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
    std::ofstream file;
};
} /* Eater */

#endif /* end of include guard: EATER_DB_HPP_ */

