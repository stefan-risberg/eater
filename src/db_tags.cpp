#include "eater/db_tags.hpp"

namespace Eater
{
    const char * DB_Tags::tb_tags = "tags";
    const char * DB_Tags::c_tags_text = "text";
    const char * DB_Tags::tb_food_tags = "food_tags";
    const char * DB_Tags::c_foods_id = "food_id";
    const char * DB_Tags::c_tags_id = "tags_id";

    DB_Tags::DB_Tags(shared_sqlite3 &db) : TableHandler(db)
    {}

    DB_Tags::~DB_Tags()
    {
        if (!close()) {
            LOGG_LN("Well this should not happen....");
        }
    }

    bool DB_Tags::init()
    {
        return true;
    }
} /* Eater */ 
