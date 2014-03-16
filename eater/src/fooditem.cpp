#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    FoodItem::FoodItem() :
        _id(-1), _name(""), _brand("")
    {}

    FoodItem::FoodItem(id_t _id,
                       const std::string &_name,
                       const std::string &_brand) :
        _id(_id), _name(_name), _brand(_brand)
    {}

    void FoodItem::id(const id_t _id)
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

    id_t FoodItem::id() const
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

    std::string FoodItem::toString() const
    {
        std::stringstream ss;
        ss << id() << " - " << ts.toString() << "\n\t"
            << "Name: " << name() << "\n\t"
            << "Brand: " << brand() << "\n\t"
            << "Tags: " << tags.toString() << "\n\t"
            << "Macro: " << mn.toString();

        return ss.str();
    }
}
