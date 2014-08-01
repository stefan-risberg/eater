#ifndef EATER_TABLE_HANDLER_HPP_
#define EATER_TABLE_HANDLER_HPP_

#include "eater/common.hpp"

namespace Eater
{
    class TableHandler
    {
    protected:
        s_db_driver db_backend;

    public:
        TableHandler(s_db_driver &db_backend);
        virtual ~TableHandler() {}

        virtual bool init() = 0;
        virtual bool close() = 0;
    };
} /* Eater */ 

#endif /* end of include guard: EATER_TABLE_HANDLER_HPP_ */

