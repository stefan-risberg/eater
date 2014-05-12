#include "eater/table_handler.hpp"

namespace Eater
{
    TableHandler::TableHandler(shared_sqlite3 &db) :
        db(db)
    {}
} /* Eater */ 
