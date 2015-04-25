#ifndef EATER_FOOD_ITEM_TAGS_HPP__
#define EATER_FOOD_ITEM_TAGS_HPP__

#include "eater/common.hpp"
#include "eater/table_handler.hpp"

namespace eater
{

struct food_tag_t {
    id_t tag_id;
    id_t food_id;
};

class food_item_tags_table_t {
 public:
    food_item_tags_table_t();
    void init(shared_session_t &s);

    void insert(food_tag_t &item, bool safe = true);
    void remove(food_tag_t &item);

    id_vec get_tags(const id_t &food_id) const;
    id_vec get_foods(const id_t &tag_id) const;

    bool contains(const food_tag_t &item) const;

    str name() const;

 private:
    shared_session_t _sql;

    id_vec get_col(const id_t &id,
                   const str &what,
                   const str &where) const;

 public:
    static const str tbl_food_tags;
    static const str col_tag_id;
    static const str col_food_id;
};

} /* eater */

#endif /* end of include guard: EATER_FOOD_ITEM_TAGS_HPP__ */

