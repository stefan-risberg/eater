#include "eater/tbl_fooditems.hpp"
#include "eater/db.hpp"
#include "format.h"
#include <fstream>
#include <cassert>

namespace Eater
{
const char *TblFoodItems::tbl_fooditems     = "fooditems";
const char *TblFoodItems::col_id            = "id";
const char *TblFoodItems::col_name          = "name";
const char *TblFoodItems::col_brand         = "brand";
const char *TblFoodItems::col_date          = "date";
const char *TblFoodItems::col_time          = "time";
const char *TblFoodItems::col_kcal          = "kcal";
const char *TblFoodItems::col_proteins      = "proteins";
const char *TblFoodItems::col_carbohydrates = "carbohydrates";
const char *TblFoodItems::col_fats          = "fats";

TblFoodItems::TblFoodItems(std::shared_ptr<DB_Driver> &db) : TableHandler(db)
{
    LOGG_MESSAGE("TblFoodItems was created.");
}

TblFoodItems::~TblFoodItems()
{
    close();
}

bool TblFoodItems::exists(const id_t item) const
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

    fmt::Writer where;
    where.Format("{}='{}'") << col_id << item;

    CHECK_RESULT(db->select(tbl_fooditems, col_id, where.str(), func));

    return result;
}

bool TblFoodItems::old(const FoodItem &item) const
{
    LOGG_MESSAGE("Check if " << item.name() << " is old.");

    fmt::Writer what;
    fmt::Writer where;
    bool result = false;

    what.Format("{},{}") << col_date << col_time;
    where.Format("{}={}") << col_id << item;

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

    CHECK_RESULT(db->select(tbl_fooditems, what.str(), where.str(), func));

    return result;
}

void TblFoodItems::update(const FoodItem &item)
{
    LOGG_MESSAGE("Try to update item " << item.name() << ".");

    fmt::Writer to;
    fmt::Writer where;

    to.Format(
        "{}={},"
        "{}={},"
        "{}='{}',"
        "{}='{}',"
        "{}={},"
        "{}={},"
        "{}={},"
        "{}={} ")
        << col_date
        << item.ts.getDate()
        << col_time
        << item.ts.getTime()
        << col_name
        << item.name()
        << col_brand
        << item.brand()
        << col_kcal
        << item.mn.calories()
        << col_proteins
        << item.mn.proteins()
        << col_carbohydrates
        << item.mn.carbohydrates()
        << col_fats
        << item.mn.fats();

    where.Format("{}={}") << col_id << item.id();

    if (!db->update(tbl_fooditems, to.str(), where.str())) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Faild to update an entry.");
    }
}

bool TblFoodItems::save(FoodItem &item)
{
    LOGG_MESSAGE("Try to save item " << item.name() << ".");

    fmt::Writer cols;
    fmt::Writer vals;

    cols.Format("{}, {}, {}, {}, {}, {}, {}, {}")
        << col_date
        << col_time
        << col_name
        << col_brand
        << col_kcal
        << col_proteins
        << col_carbohydrates
        << col_fats;

    vals.Format("{}, {}, '{}', '{}', {}, {}, {}, {}")
        << item.ts.getDate()
        << item.ts.getTime()
        << item.name()
        << item.brand()
        << item.mn.calories()
        << item.mn.proteins()
        << item.mn.carbohydrates()
        << item.mn.fats();

    CHECK_RESULT(db->insert(tbl_fooditems, cols.str(), vals.str()));

    item.id(db->getLastInsertRowId());

    return true;
}

void TblFoodItems::save(food_vec &items)
{
    for (FoodItem &it : items) {
        save(it);
    }
}

bool TblFoodItems::find(const id_t id, FoodItem &item) const
{
    fmt::Writer where;

    where.Format("{}={}") << col_id << id;

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

            item.mn.calories(db->columnInt(5));
            item.mn.proteins(db->columnDouble(6));
            item.mn.carbohydrates(db->columnDouble(7));
            item.mn.fats(db->columnDouble(8));

            found = true;
        }
    };

    CHECK_RESULT(db->select(tbl_fooditems, "*", where.str(), func));

    return found;
}

food_vec TblFoodItems::find(const id_vec &ids) const
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

bool TblFoodItems::init()
{
    if (db->tableExists(tbl_fooditems)) {
        LOGG_MESSAGE(tbl_fooditems << " exists.");
        return true;
    }

    std::vector<std::string> col_names = {
        col_id,
        col_date,
        col_time,
        col_name,
        col_brand,
        col_kcal,
        col_proteins,
        col_carbohydrates,
        col_fats
    };

    std::vector<std::string> col_types = {
        "integer primary key",
        "integer not null",
        "integer not null",
        "text not null",
        "text not null",
        "real",
        "real",
        "real",
        "real"
    };

    LOGG_MESSAGE("Try to create table " << tbl_fooditems << ".");
    return db->createTable(tbl_fooditems, col_names, col_types);
}

void TblFoodItems::close()
{
    if (db != nullptr) {
        db.reset();
    }
}

} /* Eater */
