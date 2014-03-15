#include "eater/recepie.hpp"

namespace Eater {
    Recepie::Recepie() :
        Nutrients(0.0, 0.0, 0.0, 0.0),
        _id(0), _name("")
    {}

    Recepie::Recepie(u32 _id,
                     const std::string &_name,
                     const std::vector<FoodItem> &_foods,
                     const std::vector<u32> &_amounts) :
        Nutrients(0.0, 0.0, 0.0, 0.0),
        _id(_id),
        _name(_name),
        _amounts(_amounts)
    {
        if (_amounts.size() != _foods.size()) {
            return;
        }

        for (u32 i = 0; i < _foods.size(); i++) {
            this->_foods.push_back(_foods[i].id());

            changeNutrients(_foods[i], _amounts[i]);
        }
    }

    void Recepie::id(const u32 _id)
    {
        this->_id = _id;
    }

    void Recepie::name(const std::string &_name)
    {
        this->_name = _name;
    }

    u32 Recepie::id() const
    {
        return _id;
    }

    std::string Recepie::name() const
    {
        return _name;
    }

    std::vector<u32> Recepie::foods() const
    {
        return _foods;
    }

    std::vector<u32> Recepie::amounts() const
    {
        return _amounts;
    }

    bool Recepie::foodExists(const FoodItem &food, u32 *at) const
    {
        *at = 0;
        for (u32 i = 0; i < _foods.size(); i++) {
            if (_foods.at(i) == food.id()) {
                *at = i;
                return true;
            }
        }

        return false;
    }

    bool Recepie::addFood(const FoodItem &food, const u32 amount)
    {
        if (!foodExists(food)) {
            _foods.push_back(food.id());
            _amounts.push_back(amount);

            changeNutrients(food, amount);
            
            return true;
        }
        
        return false;
    }

    bool Recepie::addFoods(const std::vector<FoodItem> &_foods,
                            const std::vector<u32> &_amounts)
    {
        if (_foods.size() != _amounts.size()) {
            return false;
        }

        bool added_one = false;
        for (u32 i = 0; i < _foods.size(); i++) {
            bool r = addFood(_foods.at(i), _amounts.at(i));

            if (r) {
                added_one = true;
            }
        }

        return added_one;
    }

    bool Recepie::removeFood(const FoodItem &food) {
        for (u32 i = 0; i < _foods.size(); i++) {
            if (_foods.at(i) == food.id()) {
                changeNutrients(food, -(_amounts[i]));

                _amounts.erase(_amounts.begin() + i);
                _foods.erase(_foods.begin() + i);

                return true;
            }
        }

        return false;
    }

    bool Recepie::removeFoods(const std::vector<FoodItem> &_foods)
    {
        bool found_one = false;
        for (auto it = _foods.begin(); it != _foods.end(); it++) {
            bool r = removeFood(*it);
            if (r) {
                found_one = true;
            }
        }

        return found_one;
    }

    bool Recepie::modifieFood(const FoodItem &food, const u32 amount)
    {
        u32 at = 0;
        bool found = foodExists(food, &at);

        if (!found) {
            return false;
        }

        auto diff = amount - _amounts[at];

        changeNutrients(food, diff);

        _amounts[at] += diff;

        return true;
    }

    void Recepie::changeNutrients(const Nutrients &item, u32 amount)
    {
        auto a = calories() + (amount * (item.calories() / 100));
        calories(a);

        a = proteins() + (amount * (item.proteins() / 100));
        proteins(a);

        a = carbohydrates() + (amount * (item.carbohydrates() / 100));
        carbohydrates(a);

        a = fats() + (amount * (item.fats() / 100));
        fats(a);
    }
}