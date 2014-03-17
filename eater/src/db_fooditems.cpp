#include "eater/db_fooditems.hpp"
#include <fstream>

static const char ca_fooditems[] = "fooditems";
static const char ca_name[] = "name";
static const char ca_brand[] = "brand";

static const char ca_recepies[] = "recepies";
static const char ca_foods[] = "foods";

static const char ca_kcal[] = "kcal";
static const char ca_proteins[] = "proteins";
static const char ca_carbohydrates[] = "carbohydrates";
static const char ca_fats[] = "fats";
static const char ca_id[] = "id";
static const char ca_date[] = "date";
static const char ca_time[] = "time";
static const char ca_tags[] = "tags";

namespace Eater
{
    DB_FoodItems::DB_FoodItems()
    {}

    bool DB_FoodItems::open(const std::string &_db)
    {
        db = nullptr;
        auto rc = sqlite3_open(_db.c_str(), &db);

        if (db == nullptr) {
            LOGG(E_RED("ERROR: "));
            LOGG("db is null\n");
            return false;
        }

        if (rc) {
            LOGG(E_RED("ERROR: "));
            LOGG("Can't open database - ");
            LOGG_LN(sqlite3_errmsg(this->db));
            return false;
        } 

        if (!init()) {
            return false;
        }

        LOGG("Opened database: ");
        LOGG_LN(_db);
        return true;
    }

    void DB_FoodItems::close()
    {
        if (db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    bool DB_FoodItems::exists(const id_t item) const
    {
        std::stringstream ss;
        ss << "select " << ca_id << " from " << ca_fooditems
            << " where id=" << item << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db, ss.str().c_str(),
                                   -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));
            return false;
        }

        r = sqlite3_step(s);

        if (r == SQLITE_DONE) {
            sqlite3_finalize(s);
            return false;
        } else if (r == SQLITE_ROW) {
            r = sqlite3_column_int(s, 0);
            sqlite3_finalize(s);

            if (r == item) {
                return true;
            }
        }

        return false;
    }

    bool DB_FoodItems::old(const FoodItem &item) const
    {
        std::stringstream ss;
        ss << "select " << ca_date << "," << ca_time
            << "from fooditems where id=" << item.id() << ";";

        sqlite3_stmt *s;

        int r = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        r = sqlite3_step(s);

        if (r == SQLITE_DONE) {
            sqlite3_finalize(s);

            return false;
        } else if (r == SQLITE_ROW) {
            TimeStamp ts(sqlite3_column_int(s, 1),
                         sqlite3_column_int(s, 0));

            sqlite3_finalize(s);
            if (item.ts > ts) {
                return false;
            }
        }

        return true;
    }

    void DB_FoodItems::update(const FoodItem &item)
    {
        std::stringstream ss;
        ss << "update " << ca_fooditems << " set "
            << ca_date << "=" << item.ts.getDate() << ", "
            << ca_time << "=" << item.ts.getTime() << ", "
            << ca_name << "='" << item.name() << "', "
            << ca_brand << "='" << item.brand() << "', "
            << ca_tags << "='" << item.tags.toString() << "', "
            << ca_kcal << "=" << item.mn.calories() << ", "
            << ca_proteins << "=" << item.mn.proteins() << ", "
            << ca_carbohydrates << "=" << item.mn.carbohydrates() << ", "
            << ca_fats << "=" << item.mn.fats()
            << " where " << ca_id << "=" << item.id() << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("update: Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return;
        }

        r = sqlite3_step(s);

        if (r != SQLITE_DONE) {
            LOGG(E_RED("ERROR: "));
            LOGG("Fiald to update, return code: ");
            LOGG_LN(E_MAGENTA(r));
        }

        sqlite3_finalize(s);
    }

    void DB_FoodItems::save(FoodItem &item)
    {
        std::stringstream ss;
        ss << "insert into fooditems (date, time, name, brand, tags, "
            << "kcal, proteins, carbohydrates, fats) "
            << "values ("
            << item.ts.getDate() << ", "
            << item.ts.getTime() << ", "
            << "'" << item.name() << "', "
            << "'" << item.brand() << "', "
            << "'" << item.tags.toString() << "', "
            << item.mn.calories() << ", "
            << item.mn.proteins() << ", "
            << item.mn.carbohydrates() << ", "
            << item.mn.fats() << ");";

        std::cout << ss.str() << std::endl;
        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("save: Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return;
        }

        r = sqlite3_step(s);

        if (r != SQLITE_DONE) {
            LOGG(E_RED("ERROR: "));
            LOGG("Fiald to update, return code: ");
            LOGG_LN(E_MAGENTA(r));
        } else {
            item.id(sqlite3_last_insert_rowid(db));
        }

        sqlite3_finalize(s);
    }

    bool DB_FoodItems::find(const id_t id, FoodItem &item) const
    {
        std::stringstream ss;
        ss << "select * from fooditems where id=" << id << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db, ss.str().c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("find: Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        r = sqlite3_step(s);

        if (r == SQLITE_DONE) {
            sqlite3_finalize(s);
            return false;
        } else if (r == SQLITE_ROW) {
            item.id(sqlite3_column_int(s, 0));
            item.ts.setDate(sqlite3_column_int(s, 1));
            item.ts.setTime(sqlite3_column_int(s, 2));
            
            ss.str(std::string()); ss << sqlite3_column_text(s, 3);
            item.name(ss.str());
            ss.str(std::string()); ss << sqlite3_column_text(s, 4);
            item.brand(ss.str());
            ss.str(std::string()); ss << sqlite3_column_text(s, 5);
            item.tags.fromString(ss.str());
            item.mn.calories(sqlite3_column_double(s, 6));
            item.mn.proteins(sqlite3_column_double(s, 7));
            item.mn.carbohydrates(sqlite3_column_double(s, 8));
            item.mn.fats(sqlite3_column_double(s, 9));

            sqlite3_finalize(s);

            return true;
        }
        LOGG(E_RED("ERROR: "));
        LOGG("Something in find didn't pan out, return code: ");
        LOGG_LN(E_MAGENTA(r));

        sqlite3_finalize(s);

        return false;
    }

    food_vec DB_FoodItems::find(const id_vec &ids) const
    {
        food_vec foods;
        FoodItem f;

        for (auto it = ids.begin(); it != ids.end(); it++) {
            if (find(*it, f)) {
                foods.push_back(f);
            }
        }

        return foods;
    }

    bool DB_FoodItems::init()
    {
        if (db == nullptr) {
            return false;
        }

        if (tableExists()) {
            return true;
        }

        std::stringstream ss;
        ss << "create table " << ca_fooditems << "("
            << ca_id << " integer primary key, "
            << ca_date << " integer not null, "
            << ca_time << " integer not null, "
            << ca_name << " text not null, "
            << ca_brand << " text not null, "
            << ca_tags << " text, "
            << ca_kcal << " real, "
            << ca_proteins << " real, "
            << ca_carbohydrates << " real, "
            << ca_fats << " real);";

        sqlite3_stmt *s;

        auto r = sqlite3_prepare_v2(db, ss.str().c_str(),  -1, &s, nullptr);
        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("init: Faild to prepare statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        r = sqlite3_step(s);

        if (r != SQLITE_DONE) {
            LOGG(E_RED("ERROR: "));
            LOGG("Faild to step statement, return code: ");
            LOGG_LN(E_MAGENTA(r));

            return false;
        }

        sqlite3_finalize(s);
        LOGG_LN("Init of database table sucessfull");

        return true;
    }

    bool DB_FoodItems::tableExists() const
    {
        std::stringstream ss;
        ss << "select count(*) from sqlite_master where type='table' and name='"
            << ca_fooditems << "';";

        sqlite3_stmt *s;

        auto r = sqlite3_prepare_v2(db , ss.str().c_str(), -1, &s, nullptr);

        if (r != SQLITE_OK) {
            LOGG(E_RED("ERROR: "));
            LOGG("Something is wrong: ");
            LOGG_LN(E_MAGENTA(r));
            return false;
        }

        r = sqlite3_step(s);

        if (r == SQLITE_DONE) {
            sqlite3_finalize(s);
            LOGG_LN("No fooditems table found");
            return false;
        }

        if (r == SQLITE_ROW) {
            r = sqlite3_column_int(s, 0);

            sqlite3_finalize(s);
            if (r == 1) {
                return true;
            } else {
                return false;
            }
        }

        sqlite3_finalize(s);
        return false;
    }

} /* Eater */ 
