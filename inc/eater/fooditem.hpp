#ifndef EATER_FOOD_ITEM_HPP

#define EATER_FOOD_ITEM_HPP

#include <vector>

#include "eater/common.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"

namespace Eater {
    class FoodItem
    {
        // Private data.
        private:
            u32 _id;
            std::string _name;
            std::string _brand;
            std::vector<std::string> _tags;
            TimeStamp _ts;

        // Public data.
        public:
            MacroNutrients macro_nutrients;

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
                     const std::string &_brand,
                     std::vector<std::string> &_tags,
                     f32 _calories,
                     f32 _proteins,
                     f32 _carbohydrates,
                     f32 _fats);

            /**
             * Constructor that initializes a default food item.
             *
             * \param _id Id of the food item.
             * \param _name Name of food.
             * \param _brand Brand of food item.
             * \param nutrients Nutrient content of food item.
             */ 
            FoodItem(u32 _id,
                     const std::string &_name,
                     const std::string &_brand,
                     std::vector<std::string> &_tags,
                     const MacroNutrients &macro_nutrients);

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
             * Update the timestamp.
             *
             * \param ts New timestamp.
             */
            void timeStamp(const TimeStamp &ts);

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

            /**
             * Get all tags for food item.
             *
             * \return Tags for food item.
             */    
            std::vector<std::string> tags();

            /**
             * Get current time stamp.
             *
             * \return Current time stamp.
             */
            TimeStamp timeStamp() const;

            /**
             * Add a tag to the food item.
             *
             * No duplicates will be added.
             *
             * \param[in] _tag Tag to add.
             * \return True if tag was added, otherwise false.
             */
            bool addTag(const std::string &tag);

            /**
             * Add tags to the food item.
             *
             * No duplicates will be added.
             *
             * \param[in] _tags Tags to be added.
             * \return True if one, some or all tags were added. If non was then false.
             */
            bool addTags(const std::vector<std::string> &_tags);

            /**
             * Remove tag.
             *
             * \param[in] tag Tag to remove.
             * \return True if tag was found and remove else false.
             */
            bool removeTag(const std::string &tag);
    };
}

#endif /* end of include guard: EATER_FOOD_ITEM_HPP */
