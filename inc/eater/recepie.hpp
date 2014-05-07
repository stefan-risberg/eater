#ifndef EATER_RECEPIE_HPP_
#define EATER_RECEPIE_HPP_

#include <vector>

#include "eater/common.hpp"
#include "eater/fooditem.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"
#include "eater/tags.hpp"

namespace Eater {
    struct amount_t
    {
        FoodItem item;
        u32 amount;
    };
    class Recepie;

    typedef std::vector<amount_t> amount_vec;
    typedef std::vector<Recepie> recepie_vec;

    class Recepie
    {
        // Private data.
        private:
            id_t _id;
            std::string _name;
            amount_vec _foods;

        // Public data.
        public:
            MacroNutrients mn; //!< Nutrients of the recepie.
            TimeStamp ts; //!< Time stamp of recepie.
            Tags tags; //!< Tags of the recepie.

        public:
            /**
             * Default constructor.
             */
            Recepie();

            /**
             * Initializer constructor.
             *
             * \param _id Id of recepie.
             * \param _name Name of recepie.
             * \param foods Foods with amounts. 
             * \param db To look upp foods nutritional value. 
             */
            Recepie(id_t _id,
                    const std::string &_name,
                    const amount_vec &foods);

            /**
             * Copy constructor.
             */
            Recepie(const Recepie &rec);

            /**
             * Move constructor.
             */
            Recepie(Recepie &&rec);

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
             * Check if a certain food is in the recepie.
             *
             * \param food Food to check if it is in the recepie,
             * \return True if it does else false.
             */
            bool foodExists(const FoodItem &food) const;

            /**
             * Adds a food item to the recepie. 
             *
             * If the food item exists the recepie nothing will change.
             *
             * \param food To add with amount. 
             * \return True if amount was added else false.
             */
            bool addFood(const amount_t &food);

            /**
             * Adds food items to the recepie.
             *
             * Duplicates will be discarded. _foods and _amounts have to have the same
             * length.
             *
             * \param foods Foods to add with amounts. 
             * \return True if one, some or all items were added else false.
             */
            bool addFoods(const amount_vec &foods);

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
            bool removeFoods(const food_vec &_foods);

            /**
             * Modify the amount of a food item in the recepie.
             *
             * \param[in] food Food item to modifie.
             * \param[in] amount New amount of the food item.
             * \return If food item was modified true else false.
             */
            bool modifyFood(const FoodItem &food, const u32 amount);

        private:
            /**
             * Change nutrient content of the recepie.
             *
             * \param[in] item Nutrient item to change by.
             * \param[in] amount Amount of the nutrient item.
             */
            void changeNutrients(const FoodItem &item, u32 amount);
    };
}

#endif /* EATER_RECEPIE_HPP_ */
