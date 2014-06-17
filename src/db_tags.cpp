#include "eater/db_tags.hpp"
#include "eater/db.hpp"
#include "format.h"
#include <cassert>

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
        if (!DB::tableExists(db, tb_tags)) {
            fmt::Writer w;
            w.Format("create table {} ("
                     "{} integer primary key,"
                     "{} text not null)")
                << tb_tags
                << c_tags_text;

            sqlite3_stmt *s = nullptr;

            assert(DB::prepare(db, w.str(), &s));

            int r = sqlite3_step(s);

            if (r != SQLITE_DONE) {
                LOGG(E_RED("ERROR: "));
                LOGG("Failed to step statement, return code: ");
                LOGG_LN(E_MAGENTA(r));

                return false;
            }

            sqlite3_finalize(s);
            LOGG("Init of database table: ");
            LOGG(tb_tags);
            LOGG_LN(", was sucessfull");
        }
        return true;
    }
} /* Eater */ 
