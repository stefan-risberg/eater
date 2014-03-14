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
             * \param[in] _calories Calorie count for 100g.
             * \param[in] _proteins Protein count for 100g.
             * \param[in] _carbohydrates Carbohydrat count for 100g.
             * \param[in] _fats Fat count for 100g.
             */
            Nutrients(f32 _calories = 0,
                      f32 _proteins = 0.0,
                      f32 _carbohydrates = 0.0,
                      f32 _fats = 0.0);

            /**
             * Set calorie count.
             *
             * \param[in] _calories New calorie count.
             */
            void calories(f32 _calories);

            /**
             * Set protein count.
             *
             * \param[in] _protins New protein count.
             */
            void proteins(f32 _proteins);

            /**
             * Set carbohydrate count.
             *
             * \param[in] _carbohydrates New carbohydrate count.
             */
            void carbohydrates(f32 _carbohydrates);
            void fats(f32 _fats);

            f32 calories() const;
            f32 proteins() const;
            f32 carbohydrates() const;
            f32 fats() const;
    };
}

#endif /* EATER_NUTRIENTS_HPP_ */

