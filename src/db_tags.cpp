#include "eater/db_tags.hpp"
#include "eater/db.hpp"
#include "format.h"
#include <cassert>
#include <vector>
#include <string>

namespace Eater
{
    const char * DB_Tags::tb_tags = "tags";
    const char * DB_Tags::c_tags_text = "text";
    const char * DB_Tags::tb_food_tags = "food_tags";
    const char * DB_Tags::c_foods_id = "food_id";
    const char * DB_Tags::c_tags_id = "tags_id";
    const char * DB_Tags::c_id = "id";

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
        if (!DB::tableExists(db, tb_tags)) {
            std::vector<std::string> col_names =
            {
                c_id,
                c_tags_text
            };

            std::vector<std::string> col_types =
            {
                "integer primary key",
                "text not null"
            };

            if (!DB::createTable(db, tb_tags, col_names, col_types)) {
                return false;
            }
        }

        if (!DB::tableExists(db, tb_food_tags)) {
            std::vector<std::string> col_names =
            {
                c_id,
                c_tags_id,
                c_foods_id
            };

            std::vector<std::string> col_types =
            {
                "integer primary key",
                "integer not null",
                "integer not null"
            };

            if (!DB::createTable(db, tb_food_tags, col_names, col_types)) {
                return false;
            }
        }

        return true;
    }
} /* Eater */ 
