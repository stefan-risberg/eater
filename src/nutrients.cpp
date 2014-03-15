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

    /**
     * Set fat count.
     *
     * \param[in] _fats New fat count.
     */
    void MacroNutrients::fats(f32 _fats)
    {
        if (_fats < 0.0) {
            _fats = 0.0;
        }
        this->_fats = _fats;
    }

    /**
     * Get calorie count.
     *
     * \return The calorie count.
     */
    f32 MacroNutrients::calories() const
    {
        return _calories;
    }

    /**
     * Get protein count.
     *
     * \return The protein count.
     */
    f32 MacroNutrients::proteins() const
    {
        return _proteins;
    }

    /**
     * Get carbohydrate count.
     *
     * \return The carbohydrate count.
     */
    f32 MacroNutrients::carbohydrates() const {
        return _carbohydrates;
    }

    /**
     * Get fat count.
     *
     * \return The fat count.
     */
    f32 MacroNutrients::fats() const {
        return _carbohydrates;
    }
}
