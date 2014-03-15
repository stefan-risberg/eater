#ifndef EATER_COMMON_HPP_
#define EATER_COMMON_HPP_

#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define DEBUG

#ifdef DEBUG
#define E_Debug(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": " << msg
#else
#define E_Debug(msg) 
#endif

#define E_BLACK(msg) "\033[1;30m" msg "\033[0m"
#define E_RED(msg) "\033[1;31m" msg "\033[0m"
#define E_GREEN(msg) "\033[1;32m" msg "\033[0m"
#define E_YELLOW(msg) "\033[1;33m" msg "\033[0m"
#define E_BLUE(msg) "\033[1;34m" msg "\033[0m"
#define E_MAGENTA(msg) "\033[1;35m" msg "\033[0m"
#define E_CYAN(msg) "\033[1;36m" msg "\033[0m"
#define E_WHITE(msg) "\033[1;37m" msg "\033[0m"

namespace Eater {
    typedef uint64_t u64;
    typedef uint32_t u32;
    typedef uint16_t u16;
    typedef uint8_t u8;

    typedef int64_t i64;
    typedef int32_t i32;
    typedef int16_t i16;
    typedef int8_t i8;

    typedef float f32;
    typedef double f64;

    template<class T> T convStrToInt(const std::string &number)
    {
        try {
            T r = std::stoi(number);
            return r;
        } catch (std::exception &e) {
            std::cerr << "Faild to convert to integer: " << number << "\n";

            return 0;
        }
    }
}

#endif /* EATER_COMMON_HPP_ */
