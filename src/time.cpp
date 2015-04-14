#include "eater/time.hpp"
#include <string>
#include <exception>
#include <format.h>

namespace Eater
{
Time::Time(const std::string &time)
{
    if (!fromString(time)) {
        setTime(0, 0, 0, 0);
    }
}

Time::Time(u8 h, u8 m, u8 s, u8 ms)
{
    setTime(h, m, s, ms);
}

Time::Time(u32 t)
{
    setTime(t);
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

void Time::setTime(u32 t)
{
    _value = t;
    hours(_hours);
    minutes(_minutes);
    seconds(_seconds);
    milliSeconds(_milli_seconds);
}

void Time::setTime(u8 h, u8 m, u8 s, u8 ms)
{
    hours(h);
    minutes(m);
    seconds(s);
    milliSeconds(ms);
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

u32 Time::getTime() const
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
    f.Format("{}:{}:{}") << hours() << minutes() << seconds();
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

std::istream &operator>>(std::istream &is, Eater::Time &t)
{
    // TODO: Fix error handeling.
    std::string h,m,s;
    int at = 0;

    // Parse until end of stream or a space.
    while(!is.failbit) {
        char c = 0;
        is.get(c);

        if (c == ':') {
            at++;
        } else if (c >= '0' || c <= '9') {
            switch (at) {
            case 0: h += c; break;
            case 1: m += c; break;
            case 2: s += c; break;
            default:
                    std::cerr
                        << "To many colon separators in input stream."
                        << std::endl;
                    return is;
            }
        } else if (c == ' ') {
            // Check if we are parsing/parsed seconds in string.
            if (at == 2) {
                break;
            } else {
                std::cerr
                    << "Incomplete time string."
                    << std::endl;
                return is;
            }
        } else {
            // if we found invalid character.
            std::cerr
                << "Expected : or a number but got: "
                << c
                << std::endl;
            return is;
        }
    }

    try {
        t.hours(std::stoi(h));
        t.minutes(std::stoi(m));
        t.seconds(std::stoi(s));
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return is;
}
