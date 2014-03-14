#ifndef EATER_FROMSTRING_TRAIT_HPP_
#define EATER_FROMSTRING_TRAIT_HPP_

#include "eater/common.hpp"

namespace Eater {
    class FromString_trait {
        public:
            virtual bool fromString(const std::string &str) = 0;
    };
}

#endif /* EATER_FROMSTRING_TRAIT_HPP_ */
