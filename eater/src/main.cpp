#include <iostream>
#include "eater/db_fooditems.hpp"


int main()
{
    Eater::DB_FoodItems db;
    db.open("fooditems.db");

    Eater::id_vec id;
    id.push_back(1);
    id.push_back(8);
    id.push_back(4);

    Eater::food_vec foods;

    foods = db.find(id);

    for (auto it = foods.begin(); it != foods.end(); it++) {
        std::cout << it->toString() << std::endl;
    }


    db.close();

    return 0;
}
