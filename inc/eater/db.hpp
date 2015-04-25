#ifndef EATER_db_t_HPP_
#define EATER_db_t_HPP_

#include <string>
#include "eater/exception.hpp"
#include "eater/common.hpp"
#include "eater/sqlinterface.hpp"
#include "eater/food_item_table.hpp"
#include "eater/tag_table.hpp"
#include "eater/food_item_tags_table.hpp"

namespace eater
{

/**
 * Database handeling for eater.
 *
 * Functions inside of Unsafe are as the name implies are unsafe, the same goes fore Safe.
 */
class db_t {
 public:
    /**
     * Connects to a database. Needs to be initialized afterworlds
     *
     * \see init
     * \param location Location of database.
     */
    db_t(const str &location);

    /**
     * Initializes all tables.
     *
     * \return if something went wrong false is returned.
     */
    bool init();

 private:
    shared_session_t _sql;

 public:
    food_item_table_t food_table;
    tag_table_t tag_table;
    food_item_tags_table_t food_tags_table;
};

typedef std::shared_ptr<db_t> shared_db_t;
typedef std::weak_ptr<db_t> weak_db_t;

} /* eater */

#endif /* end of include guard: EATER_db_t_HPP_ */

