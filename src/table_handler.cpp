#include "eater/table_handler.hpp"

namespace Eater
{
    TableHandler::TableHandler(s_db_driver &db_backend) :
        db_backend(db_backend)
    {}
} /* Eater */ 
