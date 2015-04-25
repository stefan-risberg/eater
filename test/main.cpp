#include <iostream>
#include "eater/db.hpp"
#include "eater/fooditem.hpp"
#include "eater/tags.hpp"

using namespace eater;

int main()
{
    db_t db("test.db");
    db.init();

    food_item_t it;
    it.name("Billinge original");
    it.brand("Arla");
    it.mn.set(343, 0, 26, 26);
    it.ts.now();

    try {
        db.food_table.insert(it);
        std::cout << it.to_str() << std::endl;
    } catch (const exists_already &e) {
    }

    return 0;
}
