#include "eater/time.hpp"
#include <string>
#include <exception>
#include <format.h>
#include <ctime>

namespace Eater
{
Time::Time(const std::string &time)
{
    if (!fromString(time)) {
        set(0, 0, 0, 0);
    }
}

Time::Time(u8 h, u8 m, u8 s, u8 ms)
{
    set(h, m, s, ms);
}

Time::Time(u32 t)
{
    set(t);
}

Time::Time() : Time(0, 0, 0, 0)
{
}

void Time::hours(u8 h)
{
    _hours = h;
}

void Time::minutes(u8 m)
{
    for (; m >= 60; hours(hours() + 1)) {
        m -= 60;
    }
    _minutes = m;
}

void Time::seconds(u8 s)
{
    for (; s >= 60; minutes(minutes() + 1)) {
        s -= 60;
    }

    _seconds = s;
}

void Time::milliSeconds(u8 ms)
{
    for (; ms >= 10; seconds(seconds() + 1)) {
        ms -= 10;
    }

    _milli_seconds = ms;
}

void Time::set(u32 t)
{
    _value = t;
    hours(_hours);
    minutes(_minutes);
    seconds(_seconds);
    milliSeconds(_milli_seconds);
}

void Time::set(u8 h, u8 m, u8 s, u8 ms)
{
    hours(h);
    minutes(m);
    seconds(s);
    milliSeconds(ms);
}

void Time::now()
{
    std::time_t t = std::time(0);
    struct std::tm *n = std::localtime(&t);

    set(n->tm_hour,
        n->tm_min,
        n->tm_sec);
}

u8 Time::hours() const
{
    return _hours;
}

u8 Time::minutes() const
{
    return _minutes;
}

u8 Time::seconds() const
{
    return _seconds;
}

u8 Time::milliSeconds() const
{
    return _milli_seconds;
}

u32 Time::get() const
{
    return _value;
}

bool Time::fromString(const std::string &time)
{
    std::string t = "";
    u32 state = 0;

    for (auto c : time) {
        if (c == ':' || c == '.') {
            u32 val = convStrToInt<u32>(t);
            t = "";

            switch (state) {
                case 0:
                    hours(val);
                    state++;
                    break;
                case 1:
                    minutes(val);
                    state++;
                    break;
                case 2:
                    seconds(val);
                    state++;
                    break;
                case 3:
                    std::cout << "Time format was wrong.\n";
                    std::cout << "Format: " << time << std::endl;

                    return false;
                default:
                    E_Debug("Bug has been found\n");
            }
        } else if (c >= '0' && c <= '9') {
            t += c;
        } else {
            std::cout << "Time format was wrong.\n";
            std::cout << "Format: " << time;
            std::cout << " Last read char: " << c << std::endl;

            return false;
        }
    }

    u32 val = convStrToInt<u32>(t);

    if (state == 2) {
        seconds(val);
        milliSeconds(0);
    } else if (state == 3) {
        milliSeconds(val);
    } else if (state < 3) {
        std::cout << "Time format was wrong.\n";
        std::cout << "Format: " << time << std::endl;

        return false;
    } else {
        E_Debug("Bug has been found\n");

        return false;
    }

    return true;
}

std::string Time::toString() const
{
    fmt::Writer f;
    auto add = [&f] (i32 in) {
        in < 10 ? f.Format(":0{}") << in : f.Format(":{}") << in;
    };

    f.Format("{}") << (i32)hours();
    add(minutes());
    add(seconds());
    return f.str();
}

bool Time::operator<(const Time &t) const
{
    return _value < t._value;
}

bool Time::operator<=(const Time &t) const
{
    return _value <= t._value;
}

bool Time::operator>(const Time &t) const
{
    return _value > t._value;
}

bool Time::operator>=(const Time &t) const
{
    return _value >= t._value;
}

bool Time::operator==(const Time &t) const
{
    return _value == t._value;
}

bool Time::operator!=(const Time &t) const
{
    return _value != t._value;
}
}

std::ostream &operator<<(std::ostream &os, const Eater::Time &t)
{
    return os << t.toString();
}

namespace
{
enum state {
    HOUR,
    MINUTE,
    SECOND,
    OTHER
};

state inc(state const i)
{
    switch(i) {
    case HOUR: return MINUTE;
    case MINUTE: return SECOND;
    case SECOND: return OTHER;
    default: return OTHER;
    }
}

}

std::istream &operator>>(std::istream &is, Eater::Time &t)
{
    auto at = HOUR;
    std::string time, h = "", m = "", s = "";
    is >> time;

    for (size_t i = 0; i < time.length(); i++) {
        char c = time[i];

        if (c >= '0' && c <= '9') {
            switch(at) {
            case HOUR: h += c; break;
            case MINUTE: m += c; break;
            case SECOND: s += c; break;
            default:
                         std::cerr
                             << "To meny time parts."
                             << std::endl;
                         return is;
            }
        } else if (c == ':') {
            at = inc(at);
        } else {
            std::cerr
                << "Expected : or [0-9], got: "
                << c << "." << std::endl;
            return is;
        }
    }

    try {
        t.set(std::stoi(h),
              std::stoi(m),
              std::stoi(s));
    } catch (std::exception const &e) {
        std::cerr << "Faild to convert: " << e.what() << std::endl;
    }

    return is;
}

