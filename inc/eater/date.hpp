#ifndef EATER_DATE_HPP_
#define EATER_DATE_HPP_

#include "eater/common.hpp"

namespace eater
{
/**
 * Holds a date and modifing functions.
 */
class date_t {
   private:
    union
    {
        u32 _date;
        struct
        {
            u16 _year;
            u8 _month;
            u8 _day;
        };
    };

   public:
    /**
     * Default constructor.
     */
    date_t();

    /**
     * Constructs a date.
     *
     * \param y Year.
     * \param m Month.
     * \param d Day.
     */
    date_t(u16 y, u8 m, u8 d);

    /**
     * Constructs a date.
     *
     * The first 16 bits in _date are the year, next 8 are month and
     * last are day.
     */
    date_t(u32 _date);

    /**
     * Constructs a date from a string.
     *
     * If the string is incorrect the date will be set to the beginning
     * of time.
     *
     * \param date date.
     */
    date_t(const str &date);

    /**
     * Set new date.
     *
     * \param y New year.
     * \param m New month.
     * \param d New day.
     */
    void set(u16 y, u8 m, u8 d);

    /**
     * Set new date.
     *
     * \param _date date with format: 16bit year 8bit month 8bit day.
     */
    void set(u32 _date);

    /**
     * Set new year.
     *
     * \param y New year.
     */
    void y(const u16 y);

    /**
     * Set new month.
     *
     * \param m New month.
     */
    void m(const u8 m);

    /**
     * Set new day
     *
     * \param d New day.
     */
    void d(const u8 d);

    /**
     * Sets the date to now.
     */
    void now();

    /**
     * Get whole date.
     *
     * \return Current date.
     */
    u32 get() const;

    /**
     * Get year.
     *
     * \return Year.
     */
    u16 y() const;

    /**
     * Get month.
     *
     * \return Month.
     */
    u8 m() const;

    /**
     * Get day.
     *
     * \return Day.
     */
    u8 d() const;

    /**
     * Set a new date with a string format of yyyy-mm-dd.
     *
     * \param d New date.
     * \return False if date was in wrong format.
     */
    bool from_str(const str &date);

    /**
     * Resturn date as a string.
     *
     * \return date.
     */
    str to_str() const;

    bool operator<(const date_t &t) const;
    bool operator<=(const date_t &t) const;
    bool operator>(const date_t &t) const;
    bool operator>=(const date_t &t) const;
    bool operator==(const date_t &t) const;
    bool operator!=(const date_t &t) const;
};
}

std::ostream &operator<<(std::ostream &os, const eater::date_t &d);
std::istream &operator>>(std::istream &is, eater::date_t &d);

#endif /* EATER_DATE_HPP_ */
