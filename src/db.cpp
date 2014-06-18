#include "eater/db.hpp"
#include "format.h"

namespace Eater
{
    const char * DB::tlb_fooditems = "fooditems";
    const char * DB::col_id = "id";
    const char * DB::col_name = "name";
    const char * DB::col_brand = "brand";
    const char * DB::col_date = "date";
    const char * DB::col_time = "time";
    const char * DB::col_kcal = "kcal";
    const char * DB::col_proteins = "proteins";
    const char * DB::col_carbohydrates = "carbohydrates";
    const char * DB::col_fats = "fats";
    const char * DB::col_tags = "tags";

    DB::DB() :
        food_items(nullptr)
    {}

    bool DB::open(const std::string &data_base)
    {
        sqlite3 *tmp_db = nullptr;
        int r = sqlite3_open(data_base.c_str(), &tmp_db);

        if (r != SQLITE_OK) {
            LOGG(E_RED(__PRETTY_FUNCTION__));
            LOGG(" - Faild to open database: ");
            LOGG_LN(E_MAGENTA(data_base));

            return false;
        }
        
        db = shared_sqlite3(tmp_db, sqlite3_close);
        food_items = std::shared_ptr<DB_FoodItems>(new DB_FoodItems(db));

        if (!init()) {
            return false;
        }

        LOGG("Opened database: ");
        LOGG_LN(data_base);

        return true;
    }

    bool DB::init()
    {
        auto error = [] (const std::string &table) {
            LOGG(E_RED(__PRETTY_FUNCTION__));
            LOGG(" - faild to initialize table ");
            LOGG(table);
            LOGG_LN(".");
        };

        if (db == nullptr) {
            LOGG(E_RED(__PRETTY_FUNCTION__));
            LOGG_LN(" - database pointer is null.");

            return false;
        }

        bool r = food_items->init();

        if (!r) { error("FoodItems"); return false; }

        return true;
    }

    bool DB::tableExists(shared_sqlite3 &db,
                         const std::string &table)
    {
        fmt::Writer w;
        w.Format("select count(*) from sqlite_master "
                 "where type='table' and name='{}';")
            << table;

        sqlite3_stmt *s;

        int r = sqlite3_prepare_v2(db.get(), w.c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("tableExists: Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        r = sqlite3_step(s);

        if (r == SQLITE_DONE) {
            sqlite3_finalize(s);
            LOGG_LN("No " + table + " table found.");

            return false;
        }

        if (r == SQLITE_ROW) {
            r = sqlite3_column_int(s, 0);

            sqlite3_finalize(s);

            return r == 1;
        }

        sqlite3_finalize(s);

        return false;
    }

    bool DB::prepare(const shared_sqlite3 &db,
                     const std::string &query,
                     sqlite3_stmt **st)
    {
        int r = sqlite3_prepare_v2(db.get(),
                                   query.c_str(),
                                   -1,
                                   st,
                                   nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        return true;
    }

    bool DB::createTable(shared_sqlite3 &db,
                         const std::string &table_name,
                         const std::vector<std::string> &col_name,
                         const std::vector<std::string> &col_type)
    {
        if (col_name.size() != col_type.size()) {
            LOGG(E_RED("ERROR:"));
            LOGG_LN("col_name and col_type not same size.");
            return false;
        }

        fmt::Writer w;
        w.Format("create table {} (") << table_name;

        auto col_amount = col_name.size();
        for (unsigned long i = 0; i < col_amount; i++) {
            w.Format("{} {}") << col_name[i] << col_type[i];

            if (i + 1 == col_amount) {
                w << ");";
            } else {
                w << ", ";
            }
        }

        LOGG(E_RED("SQL: "));
        LOGG_LN(w.str());

        sqlite3_stmt *s = nullptr;
        assert(DB::prepare(db, w.str(), &s));

        int r = sqlite3_step(s);

        if (r != SQLITE_DONE) {
            LOGG(E_RED("ERROR: "));
            LOGG("Faild to step statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }
        w.Clear();
        w.Format("Created table: {}") << table_name;

        LOGG_LN(w.str());

        sqlite3_finalize(s);
        return true;
    }
} /* Eater */ 
