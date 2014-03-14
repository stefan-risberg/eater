#include <iostream>
#include "eater/fooditem.hpp"
#include "eater/date.hpp"
#include "eater/time.hpp"
#include "eater/timestamp.hpp"
#include <vector>
#include <string>

int main()
{
    std::cout << "Time: " << sizeof(Eater::Time) << std::endl
        << "Date: " << sizeof(Eater::Date) << std::endl
        << "TS: " << sizeof(Eater::TimeStamp) << std::endl
        << "u32: " << sizeof(Eater::u32) << std::endl
        << "u64: " << sizeof(Eater::u64) << std::endl;

    Eater::Date d[30];

    std::cout << "Date[30]: " << sizeof(d[0]) << std::endl;

    return 0;
}
