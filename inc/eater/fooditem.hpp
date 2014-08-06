#ifndef EATER_FOOD_ITEM_HPP
#define EATER_FOOD_ITEM_HPP

#include <vector>

#include "eater/common.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"
#include "eater/tags.hpp"

namespace Eater
{
class FoodItem;

typedef std::vector<FoodItem> food_vec;

class FoodItem
{
    // Private data.
   private:
    id_t _id;
    std::string _name;
    std::string _brand;

    // Public data.
   public:
    MacroNutrients mn;  //!< Macro nutrient of Food Item.
    TimeStamp ts;       //!< Timestamp of the item.
    Tags tags;          //!< Tags for the food item.

   public:
    /**
     * Default constructor.
     */
    FoodItem();

    /**
     * Constructor that initializes a default food item.
     *
     * \param _name Name of food.
     * \param _brand Brand of food item.
     */
    FoodItem(const std::string &_name, const std::string &_brand);

    /**
     * Move constructor.
     */
    FoodItem(FoodItem &&item);

    /**
     * Copy constructor.
     */
    FoodItem(const FoodItem &item);

    /**
     * Sets food item id.
     *
     * \param[in] _id New id.
     */
    void id(const id_t _id);

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
    id_t id() const;

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
     * Creates a string representation of food item.
     *
     * \return String representation of item.
     */
    std::string toString() const;

    FoodItem &operator=(const FoodItem &it);
};
}

std::ostream &operator<<(std::ostream &os, const Eater::FoodItem &it);
std::istream &operator>>(std::istream &is, Eater::FoodItem &it);

#endif /* end of include guard: EATER_FOOD_ITEM_HPP */
