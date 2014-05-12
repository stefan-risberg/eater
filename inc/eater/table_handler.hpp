#ifndef EATER_TABLE_HANDLER_HPP_
#define EATER_TABLE_HANDLER_HPP_

#include "eater/common.hpp"

namespace Eater
{
    class TableHandler
    {
    protected:
        shared_sqlite3 db;

    public:
        TableHandler(shared_sqlite3 &db);
        virtual ~TableHandler() {}

        virtual bool init() = 0;
        virtual bool close() = 0;
    };
} /* Eater */ 

#endif /* end of include guard: EATER_TABLE_HANDLER_HPP_ */

