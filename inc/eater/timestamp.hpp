#ifndef EATER_TIMESTAMP_HPP_
#define EATER_TIMESTAMP_HPP_

#include "eater/common.hpp"
#include "eater/time.hpp"
#include "eater/date.hpp"

namespace Eater {
    /**
     * A time stamp.
     */
    class TimeStamp {
    private:
        Date _date; //!< Date of time stamp.
        Time _time; //!< Time of time stamp. 

    public:
        /**
         * Default contructor.
         */
        TimeStamp();

        /**
         * Set time and date for time stamp.
         *
         * \param t Time.
         * \param d Date.
         */
        TimeStamp(const Date &d, const Time &t);

        /**
         * Set time and date for time stamp.
         *
         * \param t Time.
         * \param d Date.  
         */
        TimeStamp(u32 d, u32 t);

        /**
         * Set time and date for new timestamp.
         *
         * \param ts Timestamp. 
         */
        TimeStamp(u64 ts);

        /**
         * Set timestamp to current time.
         */
        void setCurrent();

        /**
         * Set new date for timestamp.
         *
         * \param d New date.
         */
        void setDate(u32 d);

        /**
         * Set new date for timestamp.
         *
         * \param d New date.
         */
        void setDate(const Date &d);

        /**
         * Set new time for timestamp.
         *
         * \param t New time. 
         */
        void setTime(u32 t);

        /**
         * Set new time for timestamp.
         *
         * \param t New time. 
         */
        void setTime(const Time &t);

        
        /**
         * Set new timestamp.
         *
         * \param ts New timestamp. 
         */
        void setTimeStamp(u64 ts);
        
        /**
         * Set new timestamp.
         *
         * \param ts New timestamp. 
         */
        void setTimeStamp(const TimeStamp &ts);

        /**
         * Set new timestamp.
         *
         * \param d New date.
         * \param t New Time.  
         */
        void setTimeStamp(u32 d, u32 t);

        /**
         * Query the time.
         *
         * \return The time as a 32 bit integer.
         * \see Time
         */
        u32 getTime() const;

        /**
         * Query the date.
         *
         * \return The date as a 32 bit integer.
         * \see Date
         */
        u32 getDate() const;

        /**
         * Query the timestamp as a 64 bit integer.
         *
         * The first 32 bits are the date and the remaining are the time.
         *
         * \return Timestamp as a 64 bit integer.
         * \see Time
         * \see Date
         */
        u64 getTimeStamp() const;

        /**
         * Query for a string representation of the timestamp.
         *
         * \return String representing timestamp.
         * \see ToString_trait
         */
        std::string toString() const;

        bool operator<(const TimeStamp &ts) const;
        bool operator<=(const TimeStamp &ts) const;
        bool operator>(const TimeStamp &ts) const;
        bool operator>=(const TimeStamp &ts) const;
        bool operator==(const TimeStamp &ts) const;
        bool operator!=(const TimeStamp &ts) const;
    };
}

std::ostream& operator<<(std::ostream &os, const Eater::TimeStamp &ts);
std::istream& operator>>(std::istream &is, Eater::TimeStamp &ts);

#endif /* EATER_TIMESTAMP_HPP_ */

