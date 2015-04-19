#include "eater/sqlinterface.hpp"
#include "eater/db.hpp"

namespace  eater
{

db_t::base_exception::base_exception(const std::string &msg)
{
   _msg = msg;
}

const char* db_t::base_exception::what() const throw()
{
    return _msg.c_str();
}

db_t::not_found::not_found(const std::string &msg) :
    base_exception(msg)
{}

db_t::exists_already::exists_already(const std::string &msg) :
    base_exception(msg)
{}


} /*  eater */
