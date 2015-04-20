#ifndef EATER_TIME_HPP_
#define EATER_TIME_HPP_

#include "eater/common.hpp"

namespace eater
{
class time_t {
 private:
    union
    {
        u32 _value;

        struct
        {
            u8 _hours;
            u8 _minutes;
            u8 _seconds;
            u8 _ms;
        };
    };

 public:
    time_t(const str &time);
    /**
     * Set all time values.
     *
     * \param h Hours.
     * \param m Minutes.
     * \param s Seconds.
     * \param ms Milliseconds.
     */
    time_t(u8 h, u8 m, u8 s = 0, u8 ms = 0);

    /**
     * time_tformat is 8 bits for all time values and they are in order:
     *
     * 8-bit hour : 8-bit minute : 8-bit second : 8-bit millisecond
     *
     * \param t time_t.
     */
    time_t(u32 t);

    /**
     * Default constructor.
     */
    time_t();

    void h(u8 h);
    void m(u8 m);
    void s(u8 s);
    void ms(u8 ms);
    void set(u32 t);
    void set(u8 h, u8 m, u8 s = 0, u8 ms = 0);
    void now();

    u8 h() const;
    u8 m() const;
    u8 s() const;
    u8 ms() const;
    u32 get() const;

    bool from_str(const str &time);
    str to_str() const;

    bool operator<(const time_t &t) const;
    bool operator<=(const time_t &t) const;
    bool operator>(const time_t &t) const;
    bool operator>=(const time_t &t) const;
    bool operator==(const time_t &t) const;
    bool operator!=(const time_t &t) const;
};
}

std::ostream &operator<<(std::ostream &os, const eater::time_t &t);
std::istream &operator>>(std::istream &is, eater::time_t &t);

#endif /* EATER_TIME_HPP_ */
