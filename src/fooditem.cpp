#include "eater/fooditem.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    FoodItem::FoodItem() :
        Nutrients(0.0, 0.0, 0.0, 0.0),
        _id(0), _name(""), _brand("")
    {}

    FoodItem::FoodItem(u32 _id,
                       const std::string &_name,
                       const std::string &_brand,
                       std::vector<std::string> &_tags,
                       f32 _calories,
                       f32 _proteins,
                       f32 _carbohydrates,
                       f32 _fats) :
        Nutrients(_calories, _proteins, _carbohydrates, _fats),
        _id(_id), _name(_name), _brand(_brand), _tags(_tags)
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

    void FoodItem::timeStamp(const TimeStamp &ts)
    {
        _ts = ts;
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

    std::vector<std::string> FoodItem::tags()
    {
        return _tags;
    }

    TimeStamp FoodItem::timeStamp() const
    {
        return _ts;
    }

    bool FoodItem::addTag(const std::string &_tag)
    {
        for (auto it = _tags.begin(); it != _tags.end(); it++) {
            if (*it == _tag) {
                return false;
            }
        }

        this->_tags.push_back(_tag);
        return true;
    }

    bool FoodItem::addTags(const std::vector<std::string> &_tags)
    {
        bool added_one = false;

        for (u32 i = 0; i < _tags.size(); i++) {
            bool r = addTag(_tags[i]);

            if (r) {
                added_one = true;
            }
        }

        return added_one;
    }

    bool FoodItem::removeTag(const std::string &tag)
    {
        for (auto it = _tags.begin(); it != _tags.end(); it++) {
            if (*it == tag) {
                _tags.erase(it);
                return true;
            }
        }

        return false;
    }
}
