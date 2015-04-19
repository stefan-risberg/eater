#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"

namespace eater
{
food_item_t::food_item_t() : _id(-1), _name(""), _brand("")
{
}

food_item_t::food_item_t(const std::string &_name, const std::string &_brand)
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

void food_item_t::name(const std::string &_name)
{
    this->_name = _name;
}

void food_item_t::brand(const std::string &_brand)
{
    this->_brand = _brand;
}

id_t food_item_t::id() const
{
    return _id;
}

std::string food_item_t::name() const
{
    return _name;
}

std::string food_item_t::brand() const
{
    return _brand;
}

std::string food_item_t::to_string() const
{
    std::stringstream ss;
    ss << id() << " - " << ts.to_string() << "\n\t"
       << "Name: " << name() << "\n\t"
       << "Brand: " << brand() << "\n\t"
       << "Tags: " << tags.to_string() << "\n\t"
       << "Macro: " << mn.to_string();

    return ss.str();
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

