#ifndef EATER_DB_RECEPIES_HPP_
#define EATER_DB_RECEPIES_HPP_

#include "eater/common.hpp"
#include "eater/recepie.hpp"
#include <sqlite3.h>

namespace Eater
{
    class DB_Recepies
    {
    private:
        sqlite3 *db;

    public:
        DB_Recepies();
        bool open(const std::string &_db);
        void clone();

        bool exists(const id_t item) const;
        bool old(const Recepie &rec) const;
        void update(const Recepie &rec);
        void save(Recepie &rec);
        
        bool find(const id_t id, FoodItem &item) const;
        
    };
} /* Eater */ 

#endif /* end of include guard: EATER_DB_RECEPIES_HPP_ */

