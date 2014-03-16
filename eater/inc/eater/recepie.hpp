#ifndef EATER_RECEPIE_HPP_
#define EATER_RECEPIE_HPP_

#include <vector>

#include "eater/common.hpp"
#include "eater/fooditem.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"
#include "eater/tags.hpp"

namespace Eater {
    class Recepie
    {
        // Private data.
        private:
            id_t _id;
            std::string _name;
            std::vector<id_t> _foods;
            std::vector<u32> _amounts;

        // Public data.
        public:
            MacroNutrients macro_nutrients; //!< Nutrients of the recepie.
            TimeStamp time_stamp; //!< Time stamp of recepie.
            Tags tags; //!< Tags of the recepie.

        public:
            /**
             * Default constructor.
             */
            Recepie();

            /**
             * Initializer constructor.
             *
             * \param[in] _id Id of recepie.
             * \param[in] _name Name of recepie.
             * \param[in] _foods List of foods.
             * \param[in] _amounts Amountf of food item in the food list.
             */
            Recepie(id_t _id,
                    const std::string &_name,
                    const std::vector<FoodItem> &_foods,
                    const std::vector<u32> &_amounts);

            /**
             * Set new id for recepie.
             *
             * \param[in] _id New id.
             */
            void id(const id_t _id);

            /**
             * Set new name for recepie.
             *
             * \param[in] _name New name.
             */
            void name(const std::string &_name);

            /**
             * Get id of recepie.
             *
             * \return Id of recepie.
             */
            id_t id() const;

            /**
             * Get name of recepie.
             *
             * \return Name of recepie.
             */
            std::string name() const;

            /**
             * Get ids of all the foods in the recepie.
             *
             * \return All ids of food items.
             */
            std::vector<id_t> foods() const;

            /**
             * Get amount of food items in the recepie.
             *
             * \return Amounts of all food items.
             */
            std::vector<u32> amounts() const;

            /**
             * Check if a certain food is in the recepie.
             *
             * at will be set to 0.
             *
             * \param[in] food Food to check if it is in the recepie,
             * \param[out] at Location at where food item was found at, if no one was
             * found, value is 0.
             * \return True if it does else false.
             */
            bool foodExists(const FoodItem &food, u32 *at = nullptr) const;

            /**
             * Adds a food item to the recepie. 
             *
             * If the food item exists the recepie nothing will change.
             *
             * \param[in] food Food item to be added.
             * \param[in] amount Amount of the food added.
             * \return True if amount was added else false.
             */
            bool addFood(const FoodItem &food, const u32 amount);

            /**
             * Adds food items to the recepie.
             *
             * Duplicates will be discarded. _foods and _amounts have to have the same
             * length.
             *
             * \param[in] _foods Foods to be added.
             * \param[in] _amounts Amounts of food.
             * \return True if one, some or all items were added else false.
             */
            bool addFoods(const std::vector<FoodItem> &_foods,
                          const std::vector<u32> &_amounts);

            /**
             * Removes a food item from recepie.
             *
             * \param[in] food Food item to remove.
             * \return True if food was removed otherwise false.
             */
            bool removeFood(const FoodItem &food);

            /**
             * Removes food items from recepie.
             *
             * \param[in] _foods Food items to remove.
             * \return If one, some or all have been removed ture else false.
             */
            bool removeFoods(const std::vector<FoodItem> &_foods);

            /**
             * Modifies the amount of a food item in the recepie.
             *
             * \param[in] food Food item to modifie.
             * \param[in] amount New amount of the food item.
             * \return If food item was modified true else false.
             */
            bool modifieFood(const FoodItem &food, const u32 amount);

        private:
            /**
             * Change nutrient content of the recepie.
             *
             * \param[in] item Nutrient item to change by.
             * \param[in] amount Amount of the nutrient item.
             */
            void changeNutrients(const MacroNutrients &item, u32 amount);
    };
}

#endif /* EATER_RECEPIE_HPP_ */
