#ifndef EATER_FOOD_ITEM_HPP
#define EATER_FOOD_ITEM_HPP

#include <vector>

#include "eater/common.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"
#include "eater/tags.hpp"

namespace Eater {
    class FoodItem
    {
        // Private data.
    private:
        u32 _id;
        std::string _name;
        std::string _brand;

        // Public data.
    public:
        MacroNutrients macro_nutrients; //!< Macro nutrient of Food Item.
        TimeStamp time_stamp; //!< Timestamp of the item.
        Tags tags; //!< Tags for the food item.

    public:
        /**
         * Default constructor.
         */
        FoodItem();

        /**
         * Constructor that initializes a default food item.
         *
         * \param _id Id of the food item.
         * \param _name Name of food.
         * \param _brand Brand of food item.
         * \param _calories Calorie count for 100g of the food item.
         * \param _proteins Protein count for 100g of the food item.
         * \param _carbohydrate Carbohydrate count for 100g of food item.
         * \param _fats Fat count for 100g of food item.
         */
        FoodItem(u32 _id,
                 const std::string &_name,
                 const std::string &_brand);

        /**
         * Sets food item id.
         *
         * \param[in] _id New id.
         */
        void id(const u32 _id);

        /**
         * Set food item name.
         *
         * \oaram[in] _name New name.
         */
        void name(const std::string &_name);

        /**
         * Set brand for food item.
         *
         * \param[in] _bramd New brand.
         */
        void brand(const std::string &_brand);

        /**
         * Get food item id.
         *
         * \return Id of food item.
         */
        u32 id() const;

        /**
         * Get food item name.
         *
         * \return Name of food item.
         */
        std::string name() const;

        /**
         * Get food item brand.
         *
         * \return Brand of food item.
         */
        std::string brand() const;
    };
}

#endif /* end of include guard: EATER_FOOD_ITEM_HPP */
