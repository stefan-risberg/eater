#ifndef EATER_TIMESTAMP_HPP_
#define EATER_TIMESTAMP_HPP_

#include "eater/common.hpp"
#include "eater/time.hpp"
#include "eater/date.hpp"

namespace eater
{
/**
 * A time stamp.
 */
class time_stamp_t
{
   public:
    date_t date;  //!< date_t of time stamp.
    time_t time;  //!< time_t of time stamp.

   public:
    /**
     * Default contructor.
     */
    time_stamp_t();

    /**
     * Set time and date for time stamp.
     *
     * \param t time_t.
     * \param d date_t.
     */
    time_stamp_t(const date_t &d, const time_t &t);

    /**
     * Set time and date for time stamp.
     *
     * \param t time_t.
     * \param d date_t.
     */
    time_stamp_t(u32 d, u32 t);

    /**
     * Set time and date for new timestamp.
     *
     * \param ts time_tstamp.
     */
    time_stamp_t(u64 ts);

    /**
     * Set timestamp to current time.
     */
    void now();

    /**
     * Set new timestamp.
     *
     * \param ts New timestamp.
     */
    void set(u64 ts);

    /**
     * Set new timestamp.
     *
     * \param ts New timestamp.
     */
    void set(const time_stamp_t &ts);

    /**
     * Set new timestamp.
     *
     * \param d New date.
     * \param t New time_t.
     */
    void set(u32 d, u32 t);

    /**
     * Query the timestamp as a 64 bit integer.
     *
     * The first 32 bits are the date and the remaining are the time.
     *
     * \return time_tstamp as a 64 bit integer.
     * \see time_t
     * \see date_t
     */
    u64 get() const;

    /**
     * Query for a string representation of the timestamp.
     *
     * \return String representing timestamp.
     * \see ToString_trait
     */
    std::string to_string() const;

    bool operator<(const time_stamp_t &ts) const;
    bool operator<=(const time_stamp_t &ts) const;
    bool operator>(const time_stamp_t &ts) const;
    bool operator>=(const time_stamp_t &ts) const;
    bool operator==(const time_stamp_t &ts) const;
    bool operator!=(const time_stamp_t &ts) const;
};
}

std::ostream &operator<<(std::ostream &os, const eater::time_stamp_t &ts);
std::istream &operator>>(std::istream &is, eater::time_stamp_t &ts);

#endif /* EATER_TIMESTAMP_HPP_ */

