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

    /**
     * Initializes tags table.
     *
     * \return true if table was created.
     */
    bool initTagsTable();

    /**
     * Initializes fooditem tags table.
     *
     * \return true if table was created.
     */
    bool initFooditemTagsTable();

   public:

    /**
     * Does nothing except for passing the db pointer to parent class.
     */
    DB_Tags(std::shared_ptr<DB_Driver> &db);

    /**
     * Does nothing, everything gets destrayed at destruction of object.
     */
    virtual ~DB_Tags();

    /**
     * Initializes the tables needed to the tags database handeling.
     *
     * \return true if everything was initialized correctly, false even if
     *         partially successfull.
     */
    virtual bool init();

    /**
     * Does nothing for now.
     *
     * \return Always true.
     */
    virtual bool close();
};
} /* Eater */

#endif /* end of include guard: EATER_DB_TAGS_HPP_ */

