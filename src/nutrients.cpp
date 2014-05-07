#include "eater/nutrients.hpp"

namespace Eater {
    MacroNutrients::MacroNutrients(f32 _calories,
                                   f32 _proteins,
                                   f32 _carbohydrates,
                                   f32 _fats) :
        _calories(_calories),
        _proteins(_proteins),
        _carbohydrates(_carbohydrates),
        _fats(_fats)
    {}

    void MacroNutrients::calories(f32 _calories)
    {
        if (_calories < 0.0) {
            _calories = 0.0;
        }
        this->_calories = _calories;
    }

    void MacroNutrients::proteins(f32 _proteins)
    {
        if (_proteins < 0.0) {
            _proteins = 0.0;
        }
        this->_proteins = _proteins;
    }

    void MacroNutrients::carbohydrates(f32 _carbohydrates)
    {
        if (_carbohydrates < 0.0) {
            _carbohydrates = 0.0;
        }
        this->_carbohydrates = _carbohydrates;
    }

    void MacroNutrients::fats(f32 _fats)
    {
        if (_fats < 0.0) {
            _fats = 0.0;
        }
        this->_fats = _fats;
    }

    f32 MacroNutrients::calories() const
    {
        return _calories;
    }

    f32 MacroNutrients::proteins() const
    {
        return _proteins;
    }

    f32 MacroNutrients::carbohydrates() const {
        return _carbohydrates;
    }

    f32 MacroNutrients::fats() const {
        return _fats;
    }

    std::string MacroNutrients::toString() const
    {
        std::stringstream ss;
        ss << "Kcal: " << calories()
            << " Proteins: " << proteins()
            << " Carbohydrates: " << carbohydrates()
            << " Fats: " << fats();

        return ss.str();
    }

}
