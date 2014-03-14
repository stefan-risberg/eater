#ifndef EATER_TOSTRING_TRAIT_HPP_
#define EATER_TOSTRING_TRAIT_HPP_

#include "eater/common.hpp"

namespace Eater {
    class ToString_trait {
        public:
            virtual std::string toString() const = 0;
    };
}

#endif /* EATER_TOSTRING_TRAIT_HPP_ */
