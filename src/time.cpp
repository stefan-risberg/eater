#include "eater/time.hpp"
#include <string>
#include <exception>
#include <format.h>
#include <ctime>

namespace eater
{
time_t::time_t(const std::string &time)
{
    if (!from_string(time)) {
        set(0, 0, 0, 0);
    }
}

time_t::time_t(u8 h, u8 m, u8 s, u8 ms)
{
    set(h, m, s, ms);
}

time_t::time_t(u32 t)
{
    set(t);
}

time_t::time_t() : time_t(0, 0, 0, 0)
{
}

void time_t::h(u8 h)
{
    _hours = h;
}

void time_t::m(u8 m)
{
    for (; m >= 60; h(h() + 1)) {
        m -= 60;
    }
    _minutes = m;
}

void time_t::s(u8 s)
{
    for (; s >= 60; m(m() + 1)) {
        s -= 60;
    }

    _seconds = s;
}

void time_t::ms(u8 ms)
{
    for (; ms >= 10; s(s() + 1)) {
        ms -= 10;
    }

    _ms = ms;
}

void time_t::set(u32 t)
{
    _value = t;
    // We do this to validate so that minutes isn't bigger then 60.
    m(_minutes);
    s(_seconds);
    ms(_ms);
}

void time_t::set(u8 h, u8 m, u8 s, u8 ms)
{
    this->h(h);
    this->m(m);
    this->s(s);
    this->ms(ms);
}

void time_t::now()
{
    std::time_t t = std::time(0);
    struct std::tm *n = std::localtime(&t);

    set(n->tm_hour,
        n->tm_min,
        n->tm_sec);
}

u8 time_t::h() const
{
    return _hours;
}

u8 time_t::m() const
{
    return _minutes;
}

u8 time_t::s() const
{
    return _seconds;
}

u8 time_t::ms() const
{
    return _ms;
}

u32 time_t::get() const
{
    return _value;
}

bool time_t::from_string(const std::string &time)
{
    std::string t = "";
    u32 state = 0;

    for (auto c : time) {
        if (c == ':' || c == '.') {
            u32 val = std::stoi(t);
            t = "";

            switch (state) {
                case 0:
                    h(val);
                    state++;
                    break;
                case 1:
                    m(val);
                    state++;
                    break;
                case 2:
                    s(val);
                    state++;
                    break;
                case 3:
                    std::cout << "time_t format was wrong.\n";
                    std::cout << "Format: " << time << std::endl;

                    return false;
                default:
                    E_Debug("Bug has been found\n");
            }
        } else if (c >= '0' && c <= '9') {
            t += c;
        } else {
            std::cout << "time_t format was wrong.\n";
            std::cout << "Format: " << time;
            std::cout << " Last read char: " << c << std::endl;

            return false;
        }
    }

    u32 val = std::stoi(t);

    if (state == 2) {
        s(val);
        ms(0);
    } else if (state == 3) {
        ms(val);
    } else if (state < 3) {
        std::cout << "time_t format was wrong.\n";
        std::cout << "Format: " << time << std::endl;

        return false;
    } else {
        E_Debug("Bug has been found\n");

        return false;
    }

    return true;
}

std::string time_t::to_string() const
{
    fmt::Writer f;
    auto add = [&f] (i32 in) {
        in < 10 ? f.Format(":0{}") << in : f.Format(":{}") << in;
    };

    f.Format("{}") << (i32)h();
    add(m());
    add(s());
    return f.str();
}

bool time_t::operator<(const time_t &t) const
{
    return _value < t._value;
}

bool time_t::operator<=(const time_t &t) const
{
    return _value <= t._value;
}

bool time_t::operator>(const time_t &t) const
{
    return _value > t._value;
}

bool time_t::operator>=(const time_t &t) const
{
    return _value >= t._value;
}

bool time_t::operator==(const time_t &t) const
{
    return _value == t._value;
}

bool time_t::operator!=(const time_t &t) const
{
    return _value != t._value;
}
}

std::ostream &operator<<(std::ostream &os, const eater::time_t &t)
{
    return os << t.to_string();
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

std::istream &operator>>(std::istream &is, eater::time_t &t)
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

