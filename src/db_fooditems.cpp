#include "eater/db_fooditems.hpp"
#include "eater/db.hpp"
#include "format.h"
#include <fstream>
#include <cassert>

namespace Eater
{
const char *DB_FoodItems::fooditems = "fooditems";
const char *DB_FoodItems::id = "id";
const char *DB_FoodItems::name = "name";
const char *DB_FoodItems::brand = "brand";
const char *DB_FoodItems::date = "date";
const char *DB_FoodItems::time = "time";
const char *DB_FoodItems::kcal = "kcal";
const char *DB_FoodItems::proteins = "proteins";
const char *DB_FoodItems::carbohydrates = "carbohydrates";
const char *DB_FoodItems::fats = "fats";
const char *DB_FoodItems::tags = "tags";

DB_FoodItems::DB_FoodItems(std::shared_ptr<DB_Driver> &db) : TableHandler(db)
{
    LOGG_MESSAGE("DB_FoodItems was created.");
}

DB_FoodItems::~DB_FoodItems()
{
    if (!close()) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " Well this should not happen...");
    }
}

bool DB_FoodItems::exists(const id_t item) const
{
    LOGG_MESSAGE("Check if " << item << " exists.");
    bool result = false;
    std::function<void()> func = [&]() {
        auto r = db->step();

        if (r == Sql::DONE) {
            result = false;
        } else if (r == Sql::ROW) {
            auto ret_id = db->columnInt(0);

            if (item == ret_id) {
                result = true;
            }
        }
    };

    fmt::Writer w;
    w.Format("{}={}") << id << item;

    if (!db->select(id, fooditems, w.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return result;
}

bool DB_FoodItems::old(const FoodItem &item) const
{
    LOGG_MESSAGE("Check if " << item.name() << " is old.");

    fmt::Writer what;
    fmt::Writer where;
    bool result = false;

    what.Format("{},{}") << date << time;
    where.Format("{}={}") << id << item;

    std::function<void()> func = [&]() {
        auto r = db->step();

        if (r == Sql::DONE) {
            result = false;
        } else if (r == Sql::ROW) {
            TimeStamp ts(db->columnInt(1), db->columnInt(0));

            if (item.ts < ts) {
                result = true;
            }
        } else {
            result = true;
        }
    };

    if (!db->select(what.str(), fooditems, where.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return result;
}

void DB_FoodItems::update(const FoodItem &item)
{
    LOGG_MESSAGE("Try to update item " << item.name() << ".");

    fmt::Writer to;
    fmt::Writer where;

    to.Format(
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={} ")
        << date << item.ts.getDate() << time << item.ts.getTime() << name
        << item.name() << brand << item.brand() << tags << item.tags.toString()
        << kcal << item.mn.calories() << proteins << item.mn.proteins()
        << carbohydrates << item.mn.carbohydrates() << fats << item.mn.fats();

    where.Format("{}={}") << id << item.id();

    if (db->update(fooditems, to.str(), where.str())) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to update an entry.");
    }
}

bool DB_FoodItems::save(FoodItem &item)
{
    LOGG_MESSAGE("Try to save item " << item.name() << ".");

    fmt::Writer cols;
    fmt::Writer vals;

    cols.Format("{}, {}, {}, {}, {}, {}, {}, {}, {}")
        << date << time << name << brand << tags << kcal << proteins
        << carbohydrates << fats;

    vals.Format("{}, {}, '{}', '{}', '{}', {}, {}, {}, {}")
        << item.ts.getDate() << item.ts.getTime() << item.name() << item.brand()
        << item.tags.toString() << item.mn.calories() << item.mn.proteins()
        << item.mn.carbohydrates() << item.mn.fats();

    if (!db->insert(fooditems, cols.str(), vals.str())) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << ": Faild to save item "
                                       << item.name());
        return false;
    }

    item.id(db->getLastInsertRowId());

    return true;
}

void DB_FoodItems::save(food_vec &items)
{
    for (FoodItem &it : items) {
        save(it);
    }
}

bool DB_FoodItems::find(const id_t id, FoodItem &item) const
{
    fmt::Writer where;

    where.Format("{}={}") << fooditems << this->id << id;

    bool found = false;

    std::function<void()> func = [&]() {
        auto ret = db->step();

        if (ret == Sql::DONE) {
            LOGG_MESSAGE("Didn't find: " << item.id());
            found = false;
        } else if (ret == SQLITE_ROW) {
            item.id(db->columnInt(0));
            item.ts.setDate(db->columnInt(1));
            item.ts.setTime(db->columnInt(2));

            item.name(db->columnStr(3));
            item.brand(db->columnStr(4));
            item.tags.fromString(db->columnStr(5));

            item.mn.calories(db->columnInt(6));
            item.mn.proteins(db->columnDouble(7));
            item.mn.carbohydrates(db->columnDouble(8));
            item.mn.fats(db->columnDouble(9));

            found = true;
        }
    };

    if (!db->select("*", fooditems, where.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << "Faild to select.");
        return false;
    }

    return found;
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
    if (db->tableExists(fooditems)) {
        LOGG_MESSAGE(fooditems << " exists.");
        return true;
    }

    std::vector<std::string> col_names = {
        id, date, time, name, brand, tags, kcal, proteins, carbohydrates, fats};

    std::vector<std::string> col_types = {
        "integer primary key", "integer not null", "integer not null",
        "text not null",       "text not null",    "text",
        "real",                "real",             "real",
        "real"};

    LOGG_MESSAGE("Try to create table " << fooditems << ".");
    return db->createTable(fooditems, col_names, col_types);
}
} /* Eater */
