#include "eater/food_item_table.hpp"
#include "eater/exception.hpp"

#include <format.h>
#include <string>
#include <exception>

namespace eater
{

const str food_item_table_t::tbl_fooditems = "food_items";
const str food_item_table_t::col_id        = "id";
const str food_item_table_t::col_name      = "name";
const str food_item_table_t::col_brand     = "brand";
const str food_item_table_t::col_date_time = "date_time";
const str food_item_table_t::col_kcal      = "kcal";
const str food_item_table_t::col_carbs     = "carbs";
const str food_item_table_t::col_proteins  = "proteins";
const str food_item_table_t::col_fats      = "fats";

food_item_table_t::food_item_table_t()
{}

void food_item_table_t::init(shared_session_t &s)
{
    _sql = s;
    fmt::Writer w;
    w.Format("create table if not exists {} ("
             "{} integer primary key,"
             "{} text not null,"
             "{} text not null,"
             "{} text not null,"
             "{} real not null,"
             "{} real,"
             "{} real,"
             "{} real)")
        << tbl_fooditems
        << col_id
        << col_date_time
        << col_name
        << col_brand
        << col_kcal
        << col_carbs
        << col_proteins
        << col_fats;

    *_sql << w.str();
    LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_fooditems) << ".");
}

void food_item_table_t::insert(food_item_t &it, bool safe)
{
    if (safe) {
        if (exists(it)) {
            throw exists_already("Food item exists in the table:\n"
                                 + it.to_str());
        } else if(it.id() != -1 && exists(it.id())) {
            throw exists_already("A food item with id: "
                                 + std::to_string(it.id())
                                 + " exists already in table.");
        }
    }

    if (it.id() == -1) {
        it.id(_sql->last_index(tbl_fooditems, col_id) + 1);
    }

    fmt::Writer q;

    q.Format("insert into {} ({}, {}, {}, {}, {}, {}, {}, {}) "
             "values ({}, '{}', '{}', '{}', {}, {}, {}, {});")
        << tbl_fooditems
        << col_id
        << col_date_time
        << col_name
        << col_brand
        << col_kcal
        << col_carbs
        << col_proteins
        << col_fats
        << it.id()
        << it.ts.to_str()
        << it.name()
        << it.brand()
        << it.mn.calories()
        << it.mn.carbohydrates()
        << it.mn.proteins()
        << it.mn.fats();

    *_sql << q.str();
}

void food_item_table_t::remove(food_item_t &item) {
    if (item.id() == -1) {
        throw std::invalid_argument("item.id() = -1");
    }

    fmt::Writer q;
    q.Format("delete from {} where {}={};")
        << tbl_fooditems
        << col_id
        << item.id();

    *_sql << q.str();
}

void food_item_table_t::update(food_item_t &item) {
    if (item.id() == -1) {
        throw std::invalid_argument("item.id() = -1");
    }

    fmt::Writer q;
    q.Format("update {} set "
             "{}={}, "
             "{}='{}', "
             "{}='{}', "
             "{}={}, "
             "{}={}, "
             "{}={}, "
             "{}={} "
             "where {}={}")
        << tbl_fooditems
        << col_date_time << item.ts.to_str()
        << col_name << item.name()
        << col_brand << item.brand()
        << col_kcal << item.mn.calories()
        << col_carbs << item.mn.carbohydrates()
        << col_proteins << item.mn.proteins()
        << col_fats << item.mn.fats()
        << col_id << item.id();

    *_sql << q.str();
}

food_item_t food_item_table_t::find(const id_t &id) const
{
    if (id < 0) {
        throw std::invalid_argument("id < 0");
    }

    fmt::Writer q;
    q.Format("select * from {} where {}={};")
        << tbl_fooditems
        << col_id
        << id;

    auto st = _sql->prepare(q.str());

    auto r = st.step();

    if (r != sql::ROW) {
        throw not_found("Did not found a food item with id: "
                        + std::to_string(id)
                        + ".");
    }

    food_item_t it;
    it.id(st.get_int(0));
    it.ts = time_stamp_t::from_str(st.get_str(1));
    it.name(st.get_str(2));
    it.brand(st.get_str(3));
    it.mn.calories(st.get_double(4));
    it.mn.carbohydrates(st.get_double(5));
    it.mn.proteins(st.get_double(6));
    it.mn.fats(st.get_double(7));

    return it;
}

bool food_item_table_t::exists(const id_t &id) const
{
    if (id < 0) {
        throw std::invalid_argument("id < 0");
    }

    fmt::Writer q;
    q.Format("select count({}) from {} where {}={};")
        << col_id
        << tbl_fooditems
        << col_id
        << id;

    auto st = _sql->prepare(q.str());

    if (st.step() == sql::ROW) {
        if (st.get_int(0) > 0) {
            return true;
        }
    }

    return false;
}

bool food_item_table_t::exists(const food_item_t &it) const
{
    fmt::Writer q;
    q.Format("select count({}) from {} where {}='{}' and {}='{}';")
        << col_id
        << tbl_fooditems
        << col_name << it.name()
        << col_brand << it.brand();

    auto st = _sql->prepare(q.str());

    if (st.step() == sql::ROW) {
        if (st.get_int(0) > 0) {
            return true;
        }
    }

    return false;
}

str food_item_table_t::name() const
{
    return tbl_fooditems;
}

} /* eater */
