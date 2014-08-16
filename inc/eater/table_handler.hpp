#ifndef EATER_TABLE_HANDLER_HPP_
#define EATER_TABLE_HANDLER_HPP_

#include "eater/common.hpp"
#include "eater/db_driver.hpp"
#include "eater/sql.hpp"
#include <string>
#include <memory>

namespace Eater
{
class TableHandler
{
   protected:
    std::shared_ptr<DB_Driver> db;

   public:
    TableHandler(std::shared_ptr<DB_Driver> &db);
    virtual ~TableHandler()
    {
    }

    virtual bool init() = 0;
    virtual void close() = 0;
};
} /* Eater */

#endif /* end of include guard: EATER_TABLE_HANDLER_HPP_ */

