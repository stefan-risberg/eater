#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    FoodItem::FoodItem() :
        _id(-1), _name(""), _brand("")
    {}

    FoodItem::FoodItem(const std::string &_name,
                       const std::string &_brand) :
        _id(-1), _name(_name), _brand(_brand)
    {}

    FoodItem::FoodItem(FoodItem &&item) :
        _id(std::move(item._id)),
        _name(std::move(item._name)),
        _brand(std::move(item._brand)),
        mn(std::move(item.mn)),
        ts(std::move(item.ts)),
        tags(std::move(item.tags))
    {}

    FoodItem::FoodItem(const FoodItem &item) :
        _id(item._id),
        _name(item._name),
        _brand(item._brand),
        mn(item.mn),
        ts(item.ts),
        tags(item.tags)
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

    FoodItem& FoodItem::operator=(const FoodItem &it)
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

std::ostream& operator<<(std::ostream &os, const Eater::FoodItem &it)
{
    return os << it.id() << " "
        << it.name() << " "
        << it.brand() << " "
        << it.mn << " "
        << it.ts << " "
        << it.tags;
}

std::istream& operator>>(std::istream &is, Eater::FoodItem &it)
{
    Eater::id_t id;
    std::string name, brand;
    Eater::MacroNutrients mn;
    Eater::TimeStamp ts;
    Eater::Tags tags;

    is >> id >> name >> brand >> mn >> ts >> tags;

    it.id(id);
    it.name(name);
    it.brand(brand);
    it.mn = mn;
    it.tags = tags;
    it.ts = ts;

    return is;
}

