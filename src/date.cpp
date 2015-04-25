#include "eater/date.hpp"
#include <string>
#include <exception>
#include <format.h>
#include <ctime>

namespace eater
{
date_t::date_t() : date_t(0, 0, 0)
{
}

date_t::date_t(u16 y, u8 m, u8 d)
{
    this->y(y);
    this->m(m);
    this->d(d);
}

date_t::date_t(u32 _date)
{
    set(_date);
}

date_t::date_t(const str &date)
{
    auto  d = date_t::from_str(date);

    set(d.get());
}

void date_t::set(u16 y, u8 m, u8 d)
{
    this->y(y);
    this->m(m);
    this->d(d);
}

void date_t::set(u32 _date)
{
    this->_date = _date;

    y(_year);
    m(_month);
    d(_day);
}

void date_t::y(const u16 y)
{
    _year = y;
}

void date_t::m(const u8 m)
{
    m > 12 ? _month = 12 : _month = m;
}

void date_t::d(const u8 d)
{
    d > 31 ? _day = 31 : _day = d;
}

void date_t::now()
{
    std::time_t t = std::time(0);
    struct std::tm *n = std::localtime(&t);

    set(n->tm_year + 1900,
        n->tm_mon + 1,
        n->tm_mday);
}

u32 date_t::get() const
{
    return _date;
}

u16 date_t::y() const
{
    return _year;
}

u8 date_t::m() const
{
    return _month;
}

u8 date_t::d() const
{
    return _day;
}

date_t date_t::from_str(const str &date)
{
    str tmp = "";
    u8 state = 0;
    date_t d;

    for (auto c : date) {
        if (c == '-') {
            u32 val = std::stoi(tmp);

            tmp = "";

            switch (state) {
                case 0:
                    d.y(val);
                    state++;
                    break;
                case 1:
                    d.m(val);
                    state++;
                    break;
                case 2:
                    std::cerr << "Wrong format was given...\n";
                    std::cerr << E_WHITE("Format: ") << date << std::endl;

                    throw std::invalid_argument("Malformed date: "
                                                + date
                                                + ".");
            }
        } else if (c >= '0' && c <= '9') {
            tmp += c;
        } else {
            std::cerr << "Wrong format was given...\n";
            std::cerr << E_WHITE("Format: ") << date << " last read: " << c
                      << "\n";

            throw std::invalid_argument("Malformed date: " + date + ".");
        }
    }

    if (state == 2) {
        u32 val = std::stoi(tmp);
        d.d(val);
    } else {
        E_Debug(E_RED("BUG: ") "Report it pleas.\n");

        throw std::invalid_argument("Malformed date: " + date + ".");
    }

    return d;
}

str date_t::to_str() const
{

    fmt::MemoryWriter f;

    auto add = [&f] (i32 in) {
        if (in < 10) {
            f.write("-0{}", in);
        } else {
            f.write("-{}", in);
        }
    };

    f.write("{}", (i32)y());
    add(m());
    add(d());

    return f.str();
}

bool date_t::operator<(const date_t &d) const
{
    return _date < d._date;
}

bool date_t::operator<=(const date_t &d) const
{
    return _date <= d._date;
}

bool date_t::operator>(const date_t &d) const
{
    return _date > d._date;
}

bool date_t::operator>=(const date_t &d) const
{
    return _date >= d._date;
}

bool date_t::operator==(const date_t &d) const
{
    return _date == d._date;
}

bool date_t::operator!=(const date_t &d) const
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

std::ostream &operator<<(std::ostream &os, const eater::date_t &d)
{
    return os << d.to_str();
}

std::istream &operator>>(std::istream &is, eater::date_t &d)
{
    auto at = YEAR;
    eater::str y = "", m = "", _d = "", date;
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

