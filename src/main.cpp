#include "eater/common.hpp"
#include "eater/date.hpp"
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
        test(9, d1.day() == 2);
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
