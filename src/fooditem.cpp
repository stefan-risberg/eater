#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"
#include <format.h>

namespace eater
{
food_item_t::food_item_t() : _id(-1), _name(""), _brand("")
{
}

food_item_t::food_item_t(const str &_name, const str &_brand)
    : _id(-1), _name(_name), _brand(_brand)
{
}

food_item_t::food_item_t(food_item_t &&item)
    : _id(std::move(item._id))
    , _name(std::move(item._name))
    , _brand(std::move(item._brand))
    , mn(std::move(item.mn))
    , ts(std::move(item.ts))
    , tags(std::move(item.tags))
{
}

food_item_t::food_item_t(const food_item_t &item)
    : _id(item._id)
    , _name(item._name)
    , _brand(item._brand)
    , mn(item.mn)
    , ts(item.ts)
    , tags(item.tags)
{
}

void food_item_t::id(const id_t _id)
{
    this->_id = _id;
}

void food_item_t::name(const str &_name)
{
    this->_name = _name;
}

void food_item_t::brand(const str &_brand)
{
    this->_brand = _brand;
}

id_t food_item_t::id() const
{
    return _id;
}

str food_item_t::name() const
{
    return _name;
}

str food_item_t::brand() const
{
    return _brand;
}

str food_item_t::to_str() const
{
    fmt::Writer w;
    w.Format("{} - {}\n"
             "Name: {}\n"
             "Brand: {}\n"
             "Tags: {}\n"
             "Macro: {}\n")
        << id() << ts.to_str() << name() << brand()
        << tags.to_str() << mn.to_str();

    return w.str();
}

food_item_t &food_item_t::operator=(const food_item_t &it)
{
    _id = it._id;
    _name = it._name;
    _brand = it._brand;
    mn = it.mn;
    ts = it.ts;
    tags = it.tags;

    return *this;
}
}

std::ostream &operator<<(std::ostream &os, const eater::food_item_t &it)
{
    return os << it.id() << " " << it.name() << " " << it.brand() << " "
              << it.mn << " " << it.ts << " " << it.tags;
}

