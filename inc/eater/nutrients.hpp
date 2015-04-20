#ifndef EATER_NUTRIENTS_HPP_
#define EATER_NUTRIENTS_HPP_

#include "eater/common.hpp"

namespace eater
{
class macro_nutrients_t
{
   private:
    f32 _calories;
    f32 _carbohydrates;
    f32 _proteins;
    f32 _fats;

   public:
    /**
     * Default constructor.
     *
     * \param _calories Calorie count for 100g.
     * \param _carbohydrates Carbohydrat count for 100g.
     * \param _proteins Protein count for 100g.
     * \param _fats Fat count for 100g.
     */
    macro_nutrients_t(f32 _calories = 0,
                      f32 _carbohydrates = 0.0,
                      f32 _proteins = 0.0,
                      f32 _fats = 0.0);

    /**
     * Set all values of the MacroNutrient.
     *
     * \param _calories Calorie count for 100g.
     * \param _carbohydrates Carbohydrat count for 100g.
     * \param _proteins Protein count for 100g.
     * \param _fats Fat count for 100g.
     */
    void set(f32 _calories, f32 _carbohydrates, f32 _proteins, f32 _fats);

    /**
     * Set calorie count.
     *
     * \param _calories New calorie count.
     */
    void calories(f32 _calories);

    /**
     * Set carbohydrate count.
     *
     * \param  _carbohydrates New carbohydrate count.
     */
    void carbohydrates(f32 _carbohydrates);

    /**
     * Set protein count.
     *
     * \param _protins New protein count.
     */
    void proteins(f32 _proteins);

    /**
     * Set fat count.
     *
     * \param _fats New fat count.
     */
    void fats(f32 _fats);

    /**
     * Get calorie count.
     *
     * \return Calorie count.
     */
    f32 calories() const;

    /**
     * Get protein count.
     *
     * \return Protein count.
     */
    f32 proteins() const;

    /**
     * Get carbohydrate count.
     *
     * \return Carbohydrate count.
     */
    f32 carbohydrates() const;

    /**
     * Get fat count.
     *
     * \return Fat count.
     */
    f32 fats() const;

    /**
     * Creates string representation of nutrient.
     *
     * \return String representation.
     */
    str to_str() const;
};
}

std::ostream &operator<<(std::ostream &os, const eater::macro_nutrients_t &mn);
std::istream &operator>>(std::istream &is, eater::macro_nutrients_t &mn);

#endif /* EATER_NUTRIENTS_HPP_ */

