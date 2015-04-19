#include "eater/exception.hpp"

namespace  eater
{

base_exception::base_exception(const std::string &msg)
{
   _msg = msg;
}

const char* base_exception::what() const throw()
{
    return _msg.c_str();
}

not_found::not_found(const std::string &msg) :
    base_exception(msg)
{}

exists_already::exists_already(const std::string &msg) :
    base_exception(msg)
{}

sql_error::sql_error(const str &msg) :
    base_exception(msg)
{}


} /*  eater */
