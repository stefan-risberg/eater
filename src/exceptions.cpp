#include "eater/sqlinterface.hpp"
#include "eater/db.hpp"

namespace  Eater
{

DB::BaseException::BaseException(const std::string &msg)
{
   _msg = msg;
}

const char* DB::BaseException::what() const throw()
{
    return _msg.c_str();
}

DB::NotFound::NotFound(const std::string &msg) :
    BaseException(msg)
{}

DB::ExistsAlready::ExistsAlready(const std::string &msg) :
    BaseException(msg)
{}


} /*  Eater */
