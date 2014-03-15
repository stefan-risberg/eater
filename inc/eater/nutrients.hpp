#ifndef EATER_NUTRIENTS_HPP_
#define EATER_NUTRIENTS_HPP_

#include "eater/common.hpp"

namespace Eater {
    class Nutrients {
        private:
            f32 _calories;
            f32 _proteins;
            f32 _carbohydrates;
            f32 _fats;

        public:
            /**
             * Default constructor.
             *
             * \param _calories Calorie count for 100g.
             * \param _proteins Protein count for 100g.
             * \param _carbohydrates Carbohydrat count for 100g.
             * \param _fats Fat count for 100g.
             */
            Nutrients(f32 _calories = 0,
                      f32 _proteins = 0.0,
                      f32 _carbohydrates = 0.0,
                      f32 _fats = 0.0);

            /**
             * Set calorie count.
             *
             * \param _calories New calorie count.
             */
            void calories(f32 _calories);

            /**
             * Set protein count.
             *
             * \param _protins New protein count.
             */
            void proteins(f32 _proteins);

            /**
             * Set carbohydrate count.
             *
             * \param  _carbohydrates New carbohydrate count.
             */
            void carbohydrates(f32 _carbohydrates);

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
    };
}

#endif /* EATER_NUTRIENTS_HPP_ */

