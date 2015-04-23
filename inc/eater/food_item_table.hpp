#ifndef TBL_FOOD_ITEM_HPP__
#define TBL_FOOD_ITEM_HPP__

#include "eater/common.hpp"
#include "eater/table_handler.hpp"
#include "eater/fooditem.hpp"
#include "eater/sqlinterface.hpp"

namespace eater
{
class food_item_table_t : public table_handler_t<food_item_t, id_t> {
 public:
    food_item_table_t();
    void init(shared_session_t &s);

    void insert(food_item_t &item, bool safe = true);
    void remove(food_item_t &item);
    void update(food_item_t &item);

    food_item_t find(const id_t &id) const;

    bool exists(const id_t &id) const;

    /**
     * Query table if item exists.
     *
     * Checks if a product with the same name and brand exists in the table.
     */
    bool exists(const food_item_t &item) const;

    str name() const;

 private:
    shared_session_t _sql;

 public:
    static const str tbl_fooditems;
    static const str col_id;
    static const str col_name;
    static const str col_brand;
    static const str col_date_time;
    static const str col_kcal;
    static const str col_carbs;
    static const str col_proteins;
    static const str col_fats;
};

} /* eater */

#endif /* end of include guard: TBL_FOOD_ITEM_HPP__ */

