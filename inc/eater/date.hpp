#ifndef EATER_DATE_HPP_
#define EATER_DATE_HPP_

#include "eater/common.hpp"
#include "eater/traits/to_string_trait.hpp"
#include "eater/traits/from_string_trait.hpp"

namespace Eater {
    /**
     * Holds a date and modifing functions.
     */
    class Date : public FromString_trait, public ToString_trait {
        private:
            union {
                u32 _date;
                struct {
                    u16 _year;
                    u8 _month;
                    u8 _day;
                };
            };

        public:
            /**
             * Default constructor.
             */
            Date();

            /**
             * Constructs a date.
             *
             * \param y Year.
             * \param m Month.
             * \param d Day.
             */
            Date(u16 y, u8 m, u8 d);

            /**
             * Constructs a date.
             *
             * The first 16 bits in _date are the year, next 8 are month and
             * last are day.
             */
            Date(u32 _date);
            
            /**
             * Constructs a date from a string.
             *
             * If the string is incorrect the date will be set to the beginning
             * of time.
             *
             * \param date Date.
             */
            Date(const std::string &date);
            /**
             * Set new date.
             *
             * \param y New year.
             * \param m New month.
             * \param d New day.
             */
            virtual void setDate(u16 y, u8 m, u8 d);

            /**
             * Set new date.
             *
             * \param _date Date with format: 16bit year 8bit month 8bit day.
             */
            virtual void setDate(u32 _date);

            /**
             * Set new year.
             *
             * \param y New year.
             */
            virtual void year(const u16 y);

            /**
             * Set new month.
             *
             * \param m New month.
             */
            virtual void month(const u8 m);

            /**
             * Set new day
             *
             * \param d New day.
             */
            virtual void day(const u8 d);

            /**
             * Get whole date.
             *
             * \return Current date.
             */
            u32 getDate() const;

            /**
             * Get year.
             *
             * \return Year.
             */
            u16 year() const;

            /**
             * Get month.
             *
             * \return Month.
             */
            u8 month() const;

            /**
             * Get day.
             *
             * \return Day.
             */
            u8 day() const;

            /**
             * Set a new date with a string format of yyyy-mm-dd.
             *
             * \param d New date.
             * \return False if date was in wrong format.
             */
            virtual bool fromString(const std::string &date);

            /**
             * Resturn date as a string.
             *
             * \return Date.
             */
            virtual std::string toString() const;
    };
}

#endif /* EATER_DATE_HPP_ */
