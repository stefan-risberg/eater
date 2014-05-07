#include <iostream>
#include "eater/common.hpp"
#include "eater/db.hpp"
#include "eater/db_fooditems.hpp"
#include "eater/fooditem.hpp"

int main()
{
    Eater::DB db;
    db.open("test.db");

    Eater::food_vec vec;
    Eater::FoodItem it;
    it.name("fisk");
    it.brand("abba");
    it.mn.calories(89);
    it.mn.carbohydrates(4);
    it.mn.proteins(19);
    it.mn.fats(2);
    it.ts.setCurrent();
    it.tags.addTags({"fisk", "hav", "ekologisk"});

    vec.push_back(it);

    it.name("crabba");
    it.mn.calories(101);
    it.mn.proteins(21);
    it.ts.setCurrent();
    it.tags.removeTag("fisk");
    it.tags.addTag("skaldjur");

    vec.push_back(it);

    db.food_items->save(vec);

    for (auto i : vec) {
        std::cout << i.name() << " " << i.id() << std::endl;
    }

    return 0;
}
