#include "eater/common.hpp"
#include "eater/date.hpp"
#include "eater/db.hpp"
#include "eater/fooditem.hpp"
#include <iostream>
#include <string>

#define DO_TEST

#ifdef DO_TEST
void doTest();

inline bool test(int n,
                 bool cond);
inline void printHeader(const std::string &header);

#endif //DO_TEST

int main()
{

#ifdef DO_TEST
    doTest();
#endif //DO_TEST

    return 0;
}

#ifdef DO_TEST
void doTest()
{
    // Date tests.
    printHeader("Date tests.");

    {
        Eater::Date d(2012, 1, 2);

        test(1, d.year() == 2012);
        test(2, d.month() == 1);
        test(3, d.day() == 2);

        d.year(2014);
        d.month(3);
        d.day(4);

        test(4, d.year() == 2014);
        test(5, d.month() == 3);
        test(6, d.day() == 4);

        Eater::Date d1(d.getDate());

        test(7, d1.year() == 2014);
        test(8, d1.month() == 3);
        test(9, d1.day() == 4);
    }

    printHeader("DB test.");
    {
        printHeader("TblTags tests.");
        Eater::DB db;

        db.open("test.sql");
        {
            auto id1 = db.tags->createTag("fisk");
            test(10, id1 != -1);

            auto id2 = db.tags->createTag("fågel");
            test(11, id2 != -1);

            auto id3 = db.tags->createTag("nöt");
            test(12, id3 != -1);

            test(13, db.tags->tagExists("fisk"));
            test(14, db.tags->tagExists("fågel"));
            test(15, db.tags->tagExists("nöt"));

            test(16, db.tags->getTag(id1) == "fisk");
            test(17, db.tags->getTag(id2) == "fågel");
            test(18, db.tags->getTag(id3) == "nöt");
        }
        printHeader("TblFoodItems tests.");
        {
            Eater::FoodItem pepsi("Pepsi", "Pepsi");
            pepsi.mn.set(44, 11.1, 0, 0);
            pepsi.ts.setCurrent();
            pepsi.tags.addTags({"drink", "sugar"});

            Eater::FoodItem kyckling("Kycklingfilé", "Kronfågeln");
            kyckling.mn.set(90, 0.5, 19, 1.5);
            kyckling.ts.setCurrent();
            kyckling.tags.addTags({"protein", "poultry", "good"});

            test(19, db.food_items->save(pepsi));
            test(20, db.food_items->save(kyckling));

            test(21, pepsi.id() == 1);
            test(22, kyckling.id() == 2);

            test(23, db.food_items->find(pepsi.id(), kyckling));

            test(24, kyckling.id() == pepsi.id());
            test(25, kyckling.name() == pepsi.name());
            test(26, kyckling.mn.calories() == pepsi.mn.calories());
            test(27, kyckling.mn.proteins() == pepsi.mn.proteins());

            pepsi.mn.calories(400);
            db.food_items->update(pepsi);

            Eater::FoodItem item;
            test(28, db.food_items->find(pepsi.id(), item));
            test(29, item.mn.calories() == 400);
        }
    }
}

bool test(int n,
          bool cond)
{
    if (!cond) {
        std::cout
            << E_RED("Failed    ")
            << " test: "
            << n
            << std::endl;

        return false;
    } else {
        std::cout
            << "Successful test: "
            << n
            << std::endl;

        return true;
    }
}

void printHeader(const std::string &header)
{
    for (int i = 0; i < 8; i++) {
        std::cout << "**********";
    }

    std::cout << std::endl << "** " << header << std::endl;

    for (int i = 0; i < 8; i++) {
        std::cout << "**********";
    }

    std::cout << std::endl;
}

#endif //DO_TEST
