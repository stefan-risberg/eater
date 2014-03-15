#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    FoodItem::FoodItem() :
        _id(1), _name(""), _brand("")
    {}

    FoodItem::FoodItem(u32 _id,
                       const std::string &_name,
                       const std::string &_brand) :
        _id(_id), _name(_name), _brand(_brand)
    {}

    void FoodItem::id(const u32 _id)
    {
        this->_id = _id;
    }

    void FoodItem::name(const std::string &_name)
    {
        this->_name = _name;
    }

    void FoodItem::brand(const std::string &_brand)
    {
        this->_brand = _brand;
    }

    u32 FoodItem::id() const
    {
        return _id;
    }

    std::string FoodItem::name() const
    {
        return _name;
    }

    std::string FoodItem::brand() const
    {
        return _brand;
    }
}
