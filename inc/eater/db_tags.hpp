#ifndef EATER_DB_TAGS_HPP_
#define EATER_DB_TAGS_HPP_

#include "eater/common.hpp"
#include "eater/tags.hpp"
#include "eater/table_handler.hpp"

namespace Eater
{
    class DB_Tags : TableHandler
    {
    private:
        // Tags table fields.
        static const char * tb_tags; /*!< Table name. */
        static const char * c_tags_text; /*!< Tags name column. */

        static const char * tb_food_tags;
        static const char * c_foods_id;
        static const char * c_tags_id;

        static const char * c_id;

    public:
        DB_Tags (shared_sqlite3 &db);
        virtual ~DB_Tags ();

        virtual bool init();
        virtual bool close() { return true; }
    };
} /* Eater */ 

#endif /* end of include guard: EATER_DB_TAGS_HPP_ */

