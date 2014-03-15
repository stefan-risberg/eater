#include <iostream>
#include "eater/fooditem.hpp"
#include "eater/date.hpp"
#include "eater/time.hpp"
#include "eater/timestamp.hpp"
#include "eater/nutrients.hpp"
#include "eater/tags.hpp"
#include <vector>
#include <string>

using namespace Eater;

int main()
{
    Tags t;

    t.addTag("Fisk");
    t.addTag("Lejon");
    t.addTag("Arab");

    t.addTag("Fisk");

    tags_vec tags;
    tags.push_back("Lejon");
    tags.push_back("Fisk");

    t.removeTags(tags);


    for (auto it = t.begin(); it != t.end(); it++) {
        std::cout << *it << std::endl;
    }

    return 0;
}
