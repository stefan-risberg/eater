#include "eater/timestamp.hpp"
#include <ctime>

namespace Eater
{
TimeStamp::TimeStamp() : date(), time()
{
}

TimeStamp::TimeStamp(const Date &d, const Time &t) : date(d), time(t)
{
}

TimeStamp::TimeStamp(u32 d, u32 t) : date(d), time(t)
{
}

TimeStamp::TimeStamp(u64 ts)
{
    setTimeStamp(ts);
}

void TimeStamp::now()
{
    date.now();
    time.now();
}


void TimeStamp::setTimeStamp(u64 ts)
{
    u32 t = 0x00000000FFFFFFFF & ts;
    u32 d = ts >> 32;
    date.set(d);
    time.set(t);
}

void TimeStamp::setTimeStamp(const TimeStamp &ts)
{
    date = ts.date;
    time = ts.time;
}

void TimeStamp::setTimeStamp(u32 d, u32 t)
{
    date.set(d);
    time.set(t);
}


u64 TimeStamp::getTimeStamp() const
{
    u64 ts = date.get();
    ts = ts << 32;
    ts += time.get();
    return ts;
}

std::string TimeStamp::toString() const
{
    return date.toString() + " " + time.toString();
}

bool TimeStamp::operator<(const TimeStamp &ts) const
{
    if (date < ts.date) {
        return true;
    } else if (date == ts.date && time < ts.time) {
        return true;
    }

    return false;
}

bool TimeStamp::operator<=(const TimeStamp &ts) const
{
    if (date <= ts.date) {
        return true;
    } else if (date == ts.date && time <= ts.time) {
        return true;
    }

    return false;
}

bool TimeStamp::operator>(const TimeStamp &ts) const
{
    if (date > ts.date) {
        return true;
    } else if (date == ts.date && time > ts.time) {
        return true;
    }

    return false;
}

bool TimeStamp::operator>=(const TimeStamp &ts) const
{
    if (date >= ts.date) {
        return true;
    } else if (date == ts.date && time >= ts.time) {
        return true;
    }

    return false;
}

bool TimeStamp::operator==(const TimeStamp &ts) const
{
    if (date == ts.date && time == ts.time) {
        return true;
    }

    return false;
}

bool TimeStamp::operator!=(const TimeStamp &ts) const
{
    if (date != ts.date || time != ts.time) {
        return true;
    }

    return false;
}
}

std::ostream &operator<<(std::ostream &os, const Eater::TimeStamp &ts)
{
    return os << ts.date << " " << ts.time;
}

std::istream &operator>>(std::istream &is, Eater::TimeStamp &ts)
{
    return is >> ts.date >> ts.time;
}
