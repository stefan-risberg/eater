#include "eater/date.hpp"
#include <string>
#include <exception>
#include <format.h>
#include <ctime>

namespace Eater
{
Date::Date() : Date(0, 0, 0)
{
}

Date::Date(u16 y, u8 m, u8 d)
{
    year(y);
    month(m);
    day(d);
}

Date::Date(u32 _date)
{
    set(_date);
}

Date::Date(const std::string &date)
{
    if (!fromString(date)) {
        set(0, 0, 0);
    }
}

void Date::set(u16 y, u8 m, u8 d)
{
    year(y);
    month(m);
    day(d);
}

void Date::set(u32 _date)
{
    this->_date = _date;

    year(_year);
    month(_month);
    day(_day);
}

void Date::year(const u16 y)
{
    _year = y;
}

void Date::month(const u8 m)
{
    m > 12 ? _month = 12 : _month = m;
}

void Date::day(const u8 d)
{
    d > 31 ? _day = 31 : _day = d;
}

void Date::now()
{
    std::time_t t = std::time(0);
    struct std::tm *n = std::localtime(&t);

    set(n->tm_year + 1900,
        n->tm_mon + 1,
        n->tm_mday);
}

u32 Date::get() const
{
    return _date;
}

u16 Date::year() const
{
    return _year;
}

u8 Date::month() const
{
    return _month;
}

u8 Date::day() const
{
    return _day;
}

bool Date::fromString(const std::string &date)
{
    std::string d = "";
    u8 state = 0;

    for (auto c : date) {
        if (c == '-') {
            u32 val = convStrToInt<u32>(d);

            d = "";

            switch (state) {
                case 0:
                    year(val);
                    state++;
                    break;
                case 1:
                    month(val);
                    state++;
                    break;
                case 2:
                    std::cerr << "Wrong format was given...\n";
                    std::cerr << E_WHITE("Format: ") << date << std::endl;

                    return false;
            }
        } else if (c >= '0' && c <= '9') {
            d += c;
        } else {
            std::cerr << "Wrong format was given...\n";
            std::cerr << E_WHITE("Format: ") << date << " last read: " << c
                      << "\n";

            return false;
        }
    }

    if (state == 2) {
        u32 val = convStrToInt<u32>(d);
        day(val);
    } else {
        E_Debug(E_RED("BUG: ") "Report it pleas.\n");

        return false;
    }

    return true;
}

std::string Date::toString() const
{

    fmt::Writer f;

    auto add = [&f] (i32 in) {
        if (in < 10) {
            f.Format("-0{}", in);
        } else {
            f.Format("-{}", in);
        }
    };

    f.Format("{}")
        << (i32)year();
    add(month());
    add(day());

    return f.str();
}

bool Date::operator<(const Date &d) const
{
    return _date < d._date;
}

bool Date::operator<=(const Date &d) const
{
    return _date <= d._date;
}

bool Date::operator>(const Date &d) const
{
    return _date > d._date;
}

bool Date::operator>=(const Date &d) const
{
    return _date >= d._date;
}

bool Date::operator==(const Date &d) const
{
    return _date == d._date;
}

bool Date::operator!=(const Date &d) const
{
    return _date != d._date;
}
}

namespace {
enum ParsingState {
    YEAR = 0,
    MONTH = 1,
    DAY = 2,
    OTHER
};

ParsingState inc(ParsingState p) {
    switch(p) {
    case YEAR: return MONTH;
    case MONTH: return DAY;
    case DAY: return OTHER;
    default: return OTHER;
    }
}
}

std::ostream &operator<<(std::ostream &os, const Eater::Date &d)
{
    return os << d.toString();
}

std::istream &operator>>(std::istream &is, Eater::Date &d)
{
    auto at = YEAR;
    std::string y = "", m = "", _d = "", date;
    is >> date;

    for (size_t i = 0; i < date.length(); i++) {
        char c = date[i];

        if (c == '-') {
            at = inc(at);
        } else if (c == ' ') {
            if (at == DAY) {
                break;
            } else {
                std::cerr
                    << "Faild to parse whole date stream."
                    << std::endl;
                return is;
            }
        } else if (c >= '0' && c <= '9') {
            switch(at) {
            case YEAR: y += c; break;
            case MONTH: m += c; break;
            case DAY: _d += c; break;
            default:
                      std::cerr
                          << "To many elements in date format stream."
                          << std::endl;
                      return is;
            }
        } else {
            std::cerr
                << "Expected - or [0-9] but found: "
                << c
                << "." << std::endl;
            return is;
        }
    }

    try {
        d.set(std::stoi(y),
              std::stoi(m),
              std::stoi(_d));
    } catch (std::exception const &e) {
        std::cerr << "Faild to convert string: " << e.what() << std::endl;
    }

    return is;
}

