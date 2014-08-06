#include <iostream>
#include "eater/common.hpp"
#include "eater/fooditem.hpp"
#include "eater/db.hpp"
#include "format.h"
#include "eater/sql.hpp"
#include <vector>
#include <string>

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

    std::cout << "\n\n" << it.tags.toString() << "\n\n";

    vec.push_back(it);

    it.name("crabba");
    it.mn.calories(101);
    it.mn.proteins(21);
    it.ts.setCurrent();
    it.tags.removeTag("fisk");
    it.tags.addTag("skaldjur");

    vec.push_back(it);

    LOGG_MESSAGE("test3");

    db.food_items->save(vec);

    for (auto i : vec) {
        std::cout << i.name() << " " << i.id() << std::endl;
    }

    /*std::shared_ptr<Eater::DB_Driver> db(new Eater::Sql());
    db->open("test.sql");

    if (!db->tableExists("apa")) {
        LOGG_MESSAGE("Table doesn't exist");
        db->createTable("apa", {"id", "name"}, {"integer primary key", "text"});
    }

    if (!db->insert("apa", "name", "\"fisk\"")) {
        LOGG_ERROR("Faild to insert data.");
        return 1;
    }

    //auto last_id = s.getLastInsertRowId();

    if (!db->update("apa", "name=\"grek\"", "id=2")) {
        LOGG_ERROR("Faild to update data.");
        return 2;
    }


    //std::cout << s.getLastInsertRowId() << std::endl;
    */

    return 0;
}
