#include <iostream>
#include "eater/fooditem.hpp"
#include "eater/file_db.hpp"

int main()
{
    Eater::FoodItem it("Mellanmjölk", "Arla");
    it.mn.set(45, 4.9, 3.5, 1.5);
    it.ts.setCurrent();
    it.tags.addTags({"mjölk", "färsk", "svenskt"});

    Eater::FileDB db;
    db.open("test.db");


    it.name("Bönor med tacosmak");
    it.brand("Ölands skördeprodukter");
    it.mn.set(102, 15.3, 7.2, 0.9);
    it.ts.setCurrent();
    it.tags.addTags({"bönor", "svenskt", "taco"});

    it.id(-1);


    db.close();

    return 0;
}
