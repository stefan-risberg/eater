#ifndef EATER_DB_TAGS_HPP_
#define EATER_DB_TAGS_HPP_

#include "eater/common.hpp"
#include "eater/tags.hpp"
#include "eater/table_handler.hpp"
#include "eater/db_driver.hpp"
#include <memory>

namespace Eater
{
class DB_Tags : TableHandler
{
   private:
    static const char *col_id;

    static const char *tbl_tags;
    static const char *tbl_fooditem_tags;

    static const char *col_tags_id;
    static const char *col_tags_name;
    static const char *col_fooditem_id;

   public:
    DB_Tags(std::shared_ptr<DB_Driver> &db);
    virtual ~DB_Tags();

    virtual bool init();
    virtual bool close();
};
} /* Eater */

#endif /* end of include guard: EATER_DB_TAGS_HPP_ */

