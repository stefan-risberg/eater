#ifndef EATER_TABLE_HANDLER_HPP__
#define EATER_TABLE_HANDLER_HPP__

#include "eater/common.hpp"
#include "eater/sqlinterface.hpp"

namespace eater
{

template <class T, class B>
class table_handler_t {
 public:
    virtual void init(shared_session_t &s) = 0;
    virtual void insert(T &item, bool safe = true) = 0;
    virtual void remove(T &item) = 0;
    virtual void update(T &item) = 0;

    virtual T find(const B &key) const = 0;

    virtual bool exists(const B &key) const = 0;
    virtual bool exists(const T &item) const = 0;

    virtual str name() const = 0;
};

} /* eater */

#endif /* end of include guard: EATER_TABLE_HANDLER_HPP__ */

