#include "eater/recepie.hpp"

namespace Eater {
    Recepie::Recepie() :
        _id(-1), _name(""),
        mn(0.0, 0.0, 0.0, 0.0)
    {}

    Recepie::Recepie(id_t _id,
                     const std::string &_name,
                     const amount_vec &foods,
                     const DB_FoodItems &db) :
        _id(_id),
        _name(_name),
        _foods(foods),
        mn(0.0, 0.0, 0.0, 0.0)
    {
        FoodItem item;
        // We need to fetch all food items nutritional values to add to
        // the recepie.
        for(auto it = _foods.begin(); it != _foods.end(); it++) {
            if (db.find(it->food, item)) {
                changeNutrients(item.mn, it->amount);
            }
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
        for (auto it = _foods.begin(); it != _foods.end(); it++) {
            if (it->food == food.id()) {
                return true;
            }
        }

        return false;
    }

    bool Recepie::addFood(const FoodItem &food, const u32 amount)
    {
        if (!foodExists(food)) {
            amount_t a;
            a.food = food.id();
            a.amount = amount;
            _foods.push_back(std::move(a));

            changeNutrients(food.mn, amount);
            
            return true;
        }
        
        return false;
    }

    bool Recepie::addFoods(const food_vec &_foods,
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
        for (auto it = _foods.begin(); it != _foods.end(); it++) {
            if (it->food == food.id()) {
                changeNutrients(food.mn, it->amount);
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
            if (a.food == food.id()) {
                auto diff = amount - a.amount;

                changeNutrients(food.mn, diff);
                a.amount = amount;
                return true;
            }
        }

        return false;
    }

    void Recepie::changeNutrients(const MacroNutrients &item, u32 amount)
    {
        auto a = mn.calories(); 
        a += (amount * (item.calories() / 100));

        mn.calories(a);

        a = mn.proteins(); 
        a += (amount * (item.proteins() / 100));

        mn.proteins(a);

        a = mn.carbohydrates();
        a += (amount * (item.carbohydrates() / 100));

        mn.carbohydrates(a);

        a = mn.fats();
        a += (amount * (item.fats() / 100));

        mn.fats(a);
    }
}
