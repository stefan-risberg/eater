#include "eater/timestamp.hpp"
#include <ctime>

namespace Eater {
    TimeStamp::TimeStamp(const Date &d, const Time &t) :
        Date(d), Time(t)
    {}

    TimeStamp::TimeStamp(u32 d, u32 t) :
        Date(d), Time(t)
    {}

    TimeStamp::TimeStamp() :
        Date(), Time()
    {}

    void TimeStamp::setCurrentTime()
    {
        std::time_t t = std::time(0);
        struct std::tm *now = std::localtime(&t);
        setDate(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
        setTime(now->tm_hour, now->tm_min, now->tm_sec, 0);
    }

    void TimeStamp::setTimeStamp(u64 ts)
    {
        u32 date = ts >> 32;
        u32 time = ts & 0x00000000FFFFFFFF;

        setTime(time);
        setDate(date);
    }

    void TimeStamp::setTimeStamp(u32 d, u32 t)
    {
        setTime(t);
        setDate(d);
    }

    void TimeStamp::setTimeStamp(const Date &d, const Time &t)
    {
        setTime(t.getTime());
        setDate(d.getDate());
    }

    u64 TimeStamp::getTimeStamp() const
    {
        u64 ts = getDate();
        ts <<= 32;

        ts += getTime();

        return ts;
    }

    std::string TimeStamp::toString() const
    {
        return Date::toString() + " " + Time::toString();
    }
}
