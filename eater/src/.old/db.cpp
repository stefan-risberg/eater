#include "eater/db.hpp"
#include "eater/const_data.hpp"

namespace Eater
{
    DB::DB()
    {
       food_items = std::shared_ptr<DB_FoodItems>(nullptr);
    }

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

        if (!init()) {
            return false;
        }

        db = std::shared_ptr<sqlite3>(tmp_db, sqlite3_close);

        LOGG("Opened database: ");
        LOGG_LN(data_base);

        food_items = std::shared_ptr<DB_FoodItems>(new DB_FoodItems(db));

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

        if (!tableExists(ca_fooditems)) {
            bool r = food_items->init();
            
            if (!r) {
                error(ca_fooditems);

                return false;
            }
        }

        return true;
    }

    bool DB::tableExists(const std::string &table) const
    {
        std::stringstream ss;
        ss << "select count(*) from sqlite_master where type='table' and name='"
            << table << "';";

        sqlite3_stmt *s;

        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(), -1, &s, nullptr);

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

} /* Eater */ 
