#ifndef EATER_ITEM_HPP_
#define EATER_ITEM_HPP_

#include "eater/common.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    template<class T> class Item {
        private:
            T entry;
            TimeStamp ts;

        public:
            /**
             * Build contructor.
             *
             * \param[in] entry New entry.
             * \param[in] ts Timestamp of sntry.
             */
            Item(const T &entry, const TimeStamp &ts);

            /**
             * Default constructor.
             */
            Item();

            T getEntry() const;
            TimeStamp getTimeStamp() const;

    };
}

#endif /* EATER_ITEM_HPP_ */
