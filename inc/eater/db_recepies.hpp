#ifndef EATER_DB_RECEPIES_HPP_
#define EATER_DB_RECEPIES_HPP_

#include "eater/common.hpp"
#include "eater/recepie.hpp"
#include "eater/db.hpp"

namespace Eater
{
class DB_Recepies
{
   private:
    shared_sqlite3 db;

   public:
    DB_Recepies(shared_sqlite3 &db);

    bool exists(const id_t item) const;
    bool old(const Recepie &rec) const;
    void update(const Recepie &rec);
    void save(Recepie &rec);

    bool find(const id_t id, FoodItem &item) const;
    food_vec find(const id_vec &ids) const;

    friend class DB;

   private:
    bool init();
};
} /* Eater */

#endif /* end of include guard: EATER_DB_RECEPIES_HPP_ */

