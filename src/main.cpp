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

    food_item_t it2;
    it2.name("Peppar Salami");
    it2.brand("Göl");
    it2.mn.set(427, 1, 18, 39);
    it2.ts.now();

    db.food_table.insert(it);
    db.food_table.insert(it2);

    std::cout << it.to_str() << std::endl;
    std::cout << it2.to_str() << std::endl;

    return 0;
}
