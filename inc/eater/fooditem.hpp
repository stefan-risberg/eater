#ifndef EATER_FOOD_ITEM_HPP
#define EATER_FOOD_ITEM_HPP

#include <vector>

#include "eater/common.hpp"
#include "eater/nutrients.hpp"
#include "eater/timestamp.hpp"
#include "eater/tags.hpp"

namespace eater
{
class food_item_t;

typedef std::vector<food_item_t> food_vec;

class food_item_t
{
    // Private data.
   private:
    id_t _id;
    std::string _name;
    std::string _brand;

    // Public data.
   public:
    macro_nutrients_t mn;  //!< Macro nutrient of Food Item.
    time_stamp_t ts;       //!< Timestamp of the item.
    tag_vec tags;          //!< Tags for the food item.

   public:
    /**
     * Default constructor.
     */
    food_item_t();

    /**
     * Constructor that initializes a default food item.
     *
     * \param _name Name of food.
     * \param _brand Brand of food item.
     */
    food_item_t(const std::string &_name, const std::string &_brand);

    /**
     * Move constructor.
     */
    food_item_t(food_item_t &&item);

    /**
     * Copy constructor.
     */
    food_item_t(const food_item_t &item);

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
    std::string to_string() const;

    food_item_t &operator=(const food_item_t &it);
};
}

std::ostream &operator<<(std::ostream &os, const eater::food_item_t &it);

#endif /* end of include guard: EATER_FOOD_ITEM_HPP */
