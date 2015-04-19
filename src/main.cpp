#include <iostream>
#include "eater/db.hpp"
#include "eater/fooditem.hpp"

#define C(a) a/9.2*100.0

int
main()
{
    eater::db_t db("test.db");
    if (!db.init()) {
        std::cerr << "Bummer\n";
    }

    eater::food_item_t it1("mellan mjölk", "arla");
    it1.mn.set(45, 4.9, 3.5, 1.5);
    it1.ts.date.set(2015, 4, 16);
    it1.ts.time.set(10, 30, 5);

    eater::food_item_t it2("bcaa 2:1:1", "smart supps sports nutrition");
    it2.mn.set(C(33), C(0.64), C(7.73), 0);
    it2.ts.date.set(2015, 4, 16);
    it2.ts.time.set(10, 30, 5);

    db.safe.insert(&it1);
    db.safe.insert(&it2);

    std::cout << it1.to_string() << std::endl;
    std::cout << it2.to_string() << std::endl;

    return 0;
}
