#ifndef EATER_TIME_HPP_
#define EATER_TIME_HPP_

#include "eater/common.hpp"

namespace Eater
{
class Time {
 private:
    union
    {
        u32 _value;

        struct
        {
            u8 _hours;
            u8 _minutes;
            u8 _seconds;
            u8 _milli_seconds;
        };
    };

 public:
    Time(const std::string &time);
    /**
     * Set all time values.
     *
     * \param h Hours.
     * \param m Minutes.
     * \param s Seconds.
     * \param ms Milliseconds.
     */
    Time(u8 h, u8 m, u8 s = 0, u8 ms = 0);

    /**
     * Timeformat is 8 bits for all time values and they are in order:
     *
     * 8-bit hour : 8-bit minute : 8-bit second : 8-bit millisecond
     *
     * \param t Time.
     */
    Time(u32 t);

    /**
     * Default constructor.
     */
    Time();

    void hours(u8 h);
    void minutes(u8 m);
    void seconds(u8 s);
    void milliSeconds(u8 ms);
    void setTime(u32 t);
    void setTime(u8 h, u8 m, u8 s = 0, u8 ms = 0);

    u8 hours() const;
    u8 minutes() const;
    u8 seconds() const;
    u8 milliSeconds() const;
    u32 getTime() const;

    bool fromString(const std::string &time);
    std::string toString() const;

    bool operator<(const Time &t) const;
    bool operator<=(const Time &t) const;
    bool operator>(const Time &t) const;
    bool operator>=(const Time &t) const;
    bool operator==(const Time &t) const;
    bool operator!=(const Time &t) const;
};
}

std::ostream &operator<<(std::ostream &os, const Eater::Time &t);
std::istream &operator>>(std::istream &is, Eater::Time &t);

#endif /* EATER_TIME_HPP_ */
