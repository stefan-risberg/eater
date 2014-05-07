#include "eater/date.hpp"

namespace Eater {
    Date::Date() :
        Date(0, 0, 0)
    {}

    Date::Date(u16 y, u8 m, u8 d)
    {
        year(y);
        month(m);
        day(d);
    }

    Date::Date(u32 _date)
    {
        setDate(_date);
    }

    Date::Date(const std::string &date)
    {
        if (!fromString(date)) {
            setDate(0, 0, 0);
        }
    }

    void Date::setDate(u16 y, u8 m, u8 d)
    {
        year(y);
        month(m);
        day(d);
    }

    void Date::setDate(u32 _date)
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
        d > 35 ? _day = 35 : _day = d;
    }

    u32 Date::getDate() const
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

        for(auto c: date) {
            if (c == '-') {
                u32 val = convStrToInt<u32>(d);

                d = "";

                switch(state) {
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
                std::cerr << E_WHITE("Format: ") << date
                    << " last read: " << c << "\n";

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
        u32 y = year();
        u32 m = month();
        u32 d = day();

        std::stringstream ss;

        ss << y << "-";
        
        if (m < 10)
            ss << "0";
        ss << m << "-";

        if (d < 10)
            ss << "0";
        ss << d;

        return ss.str();
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
