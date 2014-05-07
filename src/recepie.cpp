#include "eater/recepie.hpp"

namespace Eater {
    Recepie::Recepie() :
        _id(-1), _name(""),
        mn(0.0, 0.0, 0.0, 0.0)
    {}

    Recepie::Recepie(id_t _id,
                     const std::string &_name,
                     const amount_vec &foods) :
        _id(_id),
        _name(_name),
        _foods(foods),
        mn(0.0, 0.0, 0.0, 0.0)
    {
        for (auto food : _foods) {
            changeNutrients(food.item, food.amount);
        }
    }

    Recepie::Recepie(const Recepie &rec) :
        _id(rec._id),
        _name(rec._name),
        _foods(rec._foods),
        mn(rec.mn),
        ts(rec.ts),
        tags(rec.tags)
    {}

    Recepie::Recepie(Recepie &&rec) :
        _id(std::move(rec._id)),
        _name(std::move(rec._name)),
        _foods(std::move(rec._foods)),
        mn(std::move(rec.mn)),
        ts(std::move(rec.ts)),
        tags(std::move(rec.tags))
    {}

    void Recepie::id(const id_t _id)
    {
        this->_id = _id;
    }

    void Recepie::name(const std::string &_name)
    {
        this->_name = _name;
    }

    id_t Recepie::id() const
    {
        return _id;
    }

    std::string Recepie::name() const
    {
        return _name;
    }

    bool Recepie::foodExists(const FoodItem &food) const
    {
        for (auto f : _foods) {
            if (f.item.id() == food.id()) {
                return true;
            }
        }

        return false;
    }

    bool Recepie::addFood(const amount_t &food)
    {
        if (!foodExists(food.item)) {
            _foods.push_back(food);

            changeNutrients(food.item, food.amount);
            
            return true;
        }
        
        return false;
    }

    bool Recepie::addFoods(const amount_vec &foods)
    {
        bool added_one = false;

        for (auto food : foods) {
            bool r = addFood(food);

            if (r) {
                added_one = true;
            }
        }

        return added_one;
    }

    bool Recepie::removeFood(const FoodItem &food) {
        for (auto it = _foods.begin(); it != _foods.end(); it++) {
            if (it->item.id() == food.id()) {
                changeNutrients(food, it->amount);
                _foods.erase(it);

                return true;
            }
        }

        return false;
    }

    bool Recepie::removeFoods(const food_vec &_foods)
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

    bool Recepie::modifyFood(const FoodItem &food, const u32 amount)
    {
        for (auto a : _foods) {
            if (a.item.id() == food.id()) {
                auto diff = amount - a.amount;

                changeNutrients(food, diff);
                a.amount = amount;
                return true;
            }
        }

        return false;
    }

    void Recepie::changeNutrients(const FoodItem &item, u32 amount)
    {
        auto mn = item.mn;
        auto a = mn.calories(); 
        a += (amount * (mn.calories() / 100));

        mn.calories(a);

        a = mn.proteins(); 
        a += (amount * (mn.proteins() / 100));

        mn.proteins(a);

        a = mn.carbohydrates();
        a += (amount * (mn.carbohydrates() / 100));

        mn.carbohydrates(a);

        a = mn.fats();
        a += (amount * (mn.fats() / 100));

        mn.fats(a);
    }
}
