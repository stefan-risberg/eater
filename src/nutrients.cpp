#include "eater/nutrients.hpp"
#include <format.h>

namespace eater
{
macro_nutrients_t::macro_nutrients_t(f32 _calories,
                               f32 _carbohydrates,
                               f32 _proteins,
                               f32 _fats)
    : _calories(_calories)
    , _carbohydrates(_carbohydrates)
    , _proteins(_proteins)
    , _fats(_fats)
{
}

void macro_nutrients_t::set(f32 _calories,
                         f32 _carbohydrates,
                         f32 _proteins,
                         f32 _fats)
{
    calories(_calories);
    carbohydrates(_carbohydrates);
    proteins(_proteins);
    fats(_fats);
}

void macro_nutrients_t::calories(f32 _calories)
{
    if (_calories < 0.0) {
        _calories = 0.0;
    }
    this->_calories = _calories;
}

void macro_nutrients_t::carbohydrates(f32 _carbohydrates)
{
    if (_carbohydrates < 0.0) {
        _carbohydrates = 0.0;
    }
    this->_carbohydrates = _carbohydrates;
}

void macro_nutrients_t::proteins(f32 _proteins)
{
    if (_proteins < 0.0) {
        _proteins = 0.0;
    }
    this->_proteins = _proteins;
}

void macro_nutrients_t::fats(f32 _fats)
{
    if (_fats < 0.0) {
        _fats = 0.0;
    }
    this->_fats = _fats;
}

f32 macro_nutrients_t::calories() const
{
    return _calories;
}

f32 macro_nutrients_t::proteins() const
{
    return _proteins;
}

f32 macro_nutrients_t::carbohydrates() const
{
    return _carbohydrates;
}

f32 macro_nutrients_t::fats() const
{
    return _fats;
}

str macro_nutrients_t::to_str() const
{
    fmt::Writer w;
    w.Format("Kcal: {}, Carbohydrates: {}, "
             "Proteins: {}, Fats: {}.")
        << calories()
        << carbohydrates()
        << proteins()
        << fats();

    return w.str();
}
}

std::ostream &operator<<(std::ostream &os, const eater::macro_nutrients_t &mn)
{
    os << mn.calories() << " " << mn.carbohydrates() << " " << mn.proteins()
       << " " << mn.fats();

    return os;
}

std::istream &operator>>(std::istream &is, eater::macro_nutrients_t &mn)
{
    eater::f32 cal, carb, prot, fat;
    is >> cal >> carb >> prot >> fat;

    mn.calories(cal);
    mn.carbohydrates(carb);
    mn.proteins(prot);
    mn.fats(fat);

    return is;
}
