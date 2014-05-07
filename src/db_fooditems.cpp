#include "eater/db_fooditems.hpp"
#include "eater/db.hpp"
#include <fstream>

namespace Eater
{
    const char * DB_FoodItems::fooditems = "fooditems";
    const char * DB_FoodItems::id = "id";
    const char * DB_FoodItems::name = "name";
    const char * DB_FoodItems::brand = "brand";
    const char * DB_FoodItems::date = "date";
    const char * DB_FoodItems::time = "time";
    const char * DB_FoodItems::kcal = "kcal";
    const char * DB_FoodItems::proteins = "proteins";
    const char * DB_FoodItems::carbohydrates = "carbohydrates";
    const char * DB_FoodItems::fats = "fats";
    const char * DB_FoodItems::tags = "tags";

    DB_FoodItems::DB_FoodItems(shared_sqlite3 &db) :
        db(db)
    {}

    bool DB_FoodItems::exists(const id_t item) const
    {
        std::stringstream ss;
        ss << "select " << id << " from " << fooditems
            << " where id=" << item << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(),
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
        ss << "select " << date << "," << time
            << "from fooditems where id=" << item.id() << ";";

        sqlite3_stmt *s;

        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(), -1, &s, nullptr);

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
        ss << "update " << fooditems << " set "
            << date << "=" << item.ts.getDate() << ", "
            << time << "=" << item.ts.getTime() << ", "
            << name << "='" << item.name() << "', "
            << brand << "='" << item.brand() << "', "
            << tags << "='" << item.tags.toString() << "', "
            << kcal << "=" << item.mn.calories() << ", "
            << proteins << "=" << item.mn.proteins() << ", "
            << carbohydrates << "=" << item.mn.carbohydrates() << ", "
            << fats << "=" << item.mn.fats()
            << " where " << id << "=" << item.id() << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(), -1, &s, nullptr);

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

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(), -1, &s, nullptr);

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
            item.id(sqlite3_last_insert_rowid(db.get()));
        }

        sqlite3_finalize(s);
    }

    void DB_FoodItems::save(food_vec &items)
    {
        for (FoodItem &it : items) {
            save(it);
        }
    }

    bool DB_FoodItems::find(const id_t id, FoodItem &item) const
    {
        std::stringstream ss;
        ss << "select * from fooditems where id=" << id << ";";

        sqlite3_stmt *s;
        int r = sqlite3_prepare_v2(db.get(), ss.str().c_str(), -1, &s, nullptr);

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

        for (id_t id : ids) {
            if (find(id, f)) {
                foods.push_back(f);
            }
        }

        return foods;
    }

    bool DB_FoodItems::init()
    {
        if (DB::tableExists(db, fooditems)) {
            return true;
        }

        std::stringstream ss;
        ss << "create table " << fooditems << "("
            << id << " integer primary key, "
            << date << " integer not null, "
            << time << " integer not null, "
            << name << " text not null, "
            << brand << " text not null, "
            << tags << " text, "
            << kcal << " real, "
            << proteins << " real, "
            << carbohydrates << " real, "
            << fats << " real);";

        sqlite3_stmt *s;

        auto r = sqlite3_prepare_v2(db.get(), ss.str().c_str(),  -1, &s, nullptr);
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
} /* Eater */ 
