#include "eater/nutrients.hpp"

namespace Eater {
    Nutrients::Nutrients(f32 _calories,
                         f32 _proteins,
                         f32 _carbohydrates,
                         f32 _fats) :
        _calories(_calories),
        _proteins(_proteins),
        _carbohydrates(_carbohydrates),
        _fats(_fats)
    {}

    void Nutrients::calories(f32 _calories)
    {
        if (_calories < 0.0) {
            _calories = 0.0;
        }
        this->_calories = _calories;
    }

    void Nutrients::proteins(f32 _proteins)
    {
        if (_proteins < 0.0) {
            _proteins = 0.0;
        }
        this->_proteins = _proteins;
    }

    void Nutrients::carbohydrates(f32 _carbohydrates)
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
    void Nutrients::fats(f32 _fats)
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
    f32 Nutrients::calories() const
    {
        return _calories;
    }

    /**
     * Get protein count.
     *
     * \return The protein count.
     */
    f32 Nutrients::proteins() const
    {
        return _proteins;
    }

    /**
     * Get carbohydrate count.
     *
     * \return The carbohydrate count.
     */
    f32 Nutrients::carbohydrates() const {
        return _carbohydrates;
    }

    /**
     * Get fat count.
     *
     * \return The fat count.
     */
    f32 Nutrients::fats() const {
        return _carbohydrates;
    }
}
