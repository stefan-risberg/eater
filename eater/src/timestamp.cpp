#include "eater/timestamp.hpp"
#include <ctime>

namespace Eater {
    TimeStamp::TimeStamp() :
        _date(),
        _time()
    {}

    TimeStamp::TimeStamp(const Date &d, const Time &t) :
        _date(d),
        _time(t)
    {}

    TimeStamp::TimeStamp(u32 d, u32 t) :
        _date(d),
        _time(t)
    {}

    TimeStamp::TimeStamp(u64 ts)
    {
        setTimeStamp(ts);
    }

    void TimeStamp::setCurrent()
    {
        std::time_t t = std::time(0);
        struct std::tm *now = std::localtime(&t);

        _date.setDate(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
        _time.setTime(now->tm_hour, now->tm_min, now->tm_sec, 0);
    }


    void TimeStamp::setDate(u32 d)
    {
        _date.setDate(d);
    }

    void TimeStamp::setDate(const Date &d)
    {
        _date.setDate(d.getDate());
    }

    void TimeStamp::setTime(const Time &t)
    {
        _time.setTime(t.getTime());
    }

    void TimeStamp::setTime(u32 t)
    {
        _time.setTime(t);
    }

    void TimeStamp::setTimeStamp(u64 ts)
    {
        u32 time = 0x00000000FFFFFFFF & ts;
        u32 date = ts >> 32;
        _date.setDate(date);
        _time.setTime(time);
    }

    void TimeStamp::setTimeStamp(const TimeStamp &ts)
    {
        setDate(ts.getDate());
        setTime(ts.getTime());
    }

    void TimeStamp::setTimeStamp(u32 d, u32 t)
    {
        setDate(d);
        setTime(t);
    }

    u32 TimeStamp::getTime() const
    {
        return _time.getTime();
    }

    u32 TimeStamp::getDate() const
    {
        return _date.getDate();
    }

    u64 TimeStamp::getTimeStamp() const
    {
        u64 ts = _date.getDate();
        ts = ts << 32;
        ts += _time.getTime();
        return ts;
    }

    std::string TimeStamp::toString() const
    {
        return _date.toString() + " " + _time.toString();
    }

    bool TimeStamp::operator<(const TimeStamp &ts) const
    {
        if (_date < ts._date) {
            return true;
        } else if (_date == ts._date && _time < ts._time) {
            return true;
        }

        return false;
    }

    bool TimeStamp::operator<=(const TimeStamp &ts) const
    {
        if (_date <= ts._date) {
            return true;
        } else if (_date == ts._date && _time <= ts._time) {
            return true;
        }

        return false;
    }

    bool TimeStamp::operator>(const TimeStamp &ts) const
    {
        if (_date > ts._date) {
            return true;
        } else if (_date == ts._date && _time > ts._time) {
            return true;
        }

        return false;
    }

    bool TimeStamp::operator>=(const TimeStamp &ts) const
    {
        if (_date >= ts._date) {
            return true;
        } else if (_date == ts._date && _time >= ts._time) {
            return true;
        }

        return false;
    }

    bool TimeStamp::operator==(const TimeStamp &ts) const
    {
        if (_date == ts._date && _time == ts._time) {
            return true;
        }

        return false;
    }

    bool TimeStamp::operator!=(const TimeStamp &ts) const
    {
        if (_date != ts._date || _time != ts._time) {
            return true;
        }

        return false;
    }
}
