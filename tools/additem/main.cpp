#include <iostream>
#include "eater/db.hpp"
#include "eater/fooditem.hpp"
#include "eater/tags.hpp"
#include "eater/common.hpp"

using namespace eater;

void usage();
db_t init_db(const str &location);
bool add_item();
tag_vec parse_tags(const str &tags);

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage();
        return 0;
    }

    str db_location = argv[1];
    auto db = init_db(db_location);

    if (!add_item()) {
        std::cout << "Faild to add item to database." << std::endl;
    }

    return 0;
}

void usage()
{
    std::cout << "Usage: additem [db location]." << std::endl;
}

db_t init_db(const str &location)
{
    db_t db(location);
    db.init();

    return db;
}

bool add_item()
{
    food_item_t item;
    str tmp;

    std::cout << "Name: ";
    std::getline(std::cin, tmp);
    item.name(tmp);

    std::cout << "Brand: ";
    std::getline(std::cin, tmp);
    item.brand(tmp);

    std::cout << "Tags, separate with ',': ";
    std::cin >> tmp;

    item.tags = parse_tags(tmp);

    std::cout << item << std::endl;

    return true;
}

tag_vec parse_tags(const str &tags)
{
    str tag;
    tag_vec t;
    for (size_t i = 0; i < tags.length(); i++) {
        char c = tags[i];

        if (c == ',') {
            t.add(tag_t(tag));
            tag = "";
        } else {
            tag += c;
        }
    }

    t.add(tag_t(tag));

    return t;
}

