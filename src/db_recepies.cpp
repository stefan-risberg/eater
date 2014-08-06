#include "eater/db_recepies.hpp"
#include "eater/const_data.hpp"

namespace Eater
{
DB_Recepies::DB_Recepies(shared_sqlite3 &db) : db(db)
{
}

bool DB_Recepies::exists(const id_t item) const
{
}

bool DB_Recepies::old(const Recepie &rec) const
{
}

void DB_Recepies::update(const Recepie &rec)
{
}

void DB_Recepies::save(Recepie &rec)
{
}

bool DB_Recepies::find(const id_t id, FoodItem &item) const
{
}

food_vec DB_Recepies::find(const id_vec &ids) const
{
}

bool init();
} /* Eater */

