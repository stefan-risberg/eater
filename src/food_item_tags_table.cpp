#include "eater/food_item_tags_table.hpp"
#include "eater/food_item_table.hpp"
#include "eater/tag_table.hpp"
#include "eater/exception.hpp"

#include <format.h>

namespace eater
{

const str food_item_tags_table_t::tbl_food_tags = "food_tags";
const str food_item_tags_table_t::col_tag_id = "tag_id";
const str food_item_tags_table_t::col_food_id = "food_id";

food_item_tags_table_t::food_item_tags_table_t()
{}

void food_item_tags_table_t::init(shared_session_t &s)
{
    _sql = s;
    str q = fmt::format("create table if not exists {0} ("
                        "{1} integer not null,"
                        "{2} integer not null,"
                        "primary key({1}, {2}),"
                        "foreign key({1}) references {3} ({4}),"
                        "foreign key({2}) references {5} ({6}))",
                        tbl_food_tags,
                        col_tag_id,
                        col_food_id,
                        tag_table_t::tbl_tags,
                        tag_table_t::col_id,
                        food_item_table_t::tbl_fooditems,
                        food_item_table_t::col_id);

    *_sql << q;

    LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_food_tags) << ".");
}

void food_item_tags_table_t::insert(food_tag_t &item, bool safe)
{
    if (safe) {
        if (contains(item)) {
            throw exists_already ("Food item has the tag already.");
        }
    }

    str f = fmt::format("{}.{}",
                        food_item_table_t::tbl_fooditems,
                        food_item_table_t::col_id);

    str t = fmt::format("{}.{}",
                        tag_table_t::tbl_tags,
                        tag_table_t::col_id);

    *_sql << fmt::format("insert into {} values ("
                         "select {}, {} from {}, {}"
                         "where {}={} and {}={});",
                         tbl_food_tags,
                         f, t,
                         food_item_table_t::tbl_fooditems, tag_table_t::tbl_tags,
                         f, item.food_id, t, item.tag_id);
}

void food_item_tags_table_t::remove(food_tag_t &item)
{
    *_sql << fmt::format(
        "delete from {} where {}={} and {}={};",
        tbl_food_tags,
        col_food_id, item.food_id,
        col_tag_id, item.tag_id);
}

id_vec food_item_tags_table_t::get_tags(const id_t &food_id) const
{
    return get_col(food_id, col_tag_id, col_food_id);
}

id_vec food_item_tags_table_t::get_foods(const id_t &tag_id) const
{
    return get_col(tag_id, col_food_id, col_tag_id);
}

id_vec food_item_tags_table_t::get_col(const id_t &id,
                                       const str &what,
                                       const str &where) const
{
    id_vec v;

    auto st = _sql->prepare(fmt::format(
            "select {} from {} where {}={}",
            what,
            tbl_food_tags,
            where, id));

    sql::status_t r;
    while ((r = st.step()) == sql::ROW) {
        v.push_back(st.get_int(0));
    }

    if (r == sql::DONE) {
        v.shrink_to_fit();
        return v;
    }

    throw sql_error("Something whent wrong with fetching data.");
}

bool food_item_tags_table_t::contains(const food_tag_t &item) const
{
    auto st = _sql->prepare(fmt::format(
        "select count(*) from {} where {}={} and {}={};",
        tbl_food_tags,
        col_food_id, item.food_id,
        col_tag_id, item.tag_id));

    auto r = st.step();

    switch (r) {
    case sql::ROW:
        if (st.get_int(0) > 0) {
            return true;
        }
        return false;
    case sql::DONE:
        return false;
    default:
        throw sql_error ("Faild to querry if food tag pair exists.");
    }
}

str food_item_tags_table_t::name() const
{
    return tbl_food_tags;
}

} /* eater */
