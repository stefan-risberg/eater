#ifndef EATER_EXCEPTION_HPP_
#define EATER_EXCEPTION_HPP_

#include "eater/common.hpp"

#include <exception>
#include <string>

namespace eater
{

class base_exception : public std::exception {
 private:
    str _msg;

 public:
    explicit base_exception(const str &msg);
    virtual const char* what() const throw();
};

class not_found : public base_exception {
 public:
    explicit not_found(const str &msg);
};

class exists_already : public base_exception {
 public:
    explicit exists_already(const str &msg);
};

class sql_error : public base_exception {
 public:
    explicit sql_error(const str &msg);
};

} /* eater */

#endif /* end of include guard: EATER_EXCEPTION_HPP_ */

