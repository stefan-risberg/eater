#include "eater/sqlinterface.hpp"

namespace Eater
{

Statement::Statement(std::shared_ptr<sqlite3> &db, sqlite3_stmt *st)
{
    if (st == nullptr) {
        throw SqlException("Tried to initialize statement with null.");
    }

    this->st = st;
    col_count = sqlite3_column_count(st);
    this->db = db;
}

Statement::~Statement()
{
    sqlite3_finalize(st);
}

Sql::Status Statement::step()
{
    if (st == nullptr) {
        return Sql::ERROR;
    }

    auto r = sqlite3_step(st);

    switch(r) {
    case SQLITE_OK: last_status = Sql::OK; break;
    case SQLITE_ERROR: last_status = Sql::ERROR; break;
    case SQLITE_BUSY: last_status = Sql::BUSY; break;
    case SQLITE_FULL: last_status = Sql::FULL; break;
    case SQLITE_ROW: last_status = Sql::ROW; break;
    case SQLITE_DONE: last_status = Sql::DONE; break;
    default: last_status = Sql::OTHER;
    }

    return last_status;
}

Sql::Type Statement::getType(i32 col)
{
    validateBeforeGet(col);

    switch(sqlite3_column_type(st, col)) {
    case SQLITE_INTEGER: return Sql::INTEGER;
    case SQLITE_FLOAT: return Sql::DOUBLE;
    case SQLITE_TEXT: return Sql::TEXT;
    case SQLITE_BLOB: return Sql::BLOB;
    default: return Sql::NONE;
    }
}

i32 Statement::getInt(i32 col)
{
    validateBeforeGet(col);
    return sqlite3_column_int(st, col);
}

f64 Statement::getDouble(i32 col)
{
    validateBeforeGet(col);
    return sqlite3_column_double(st, col);
}

std::string Statement::getStr(i32 col)
{
    validateBeforeGet(col);
    return std::string(
        reinterpret_cast<const char *> (sqlite3_column_text(st, col)));
}

void Statement::validateBeforeGet(i32 col)
{
    if (st == nullptr) {
        throw SqlException("No prepared statement.");
    }

    if (last_status != Sql::ROW) {
        throw SqlException("No row to extract data from.");
    }

    if (col >= col_count) {
        throw SqlException("Out of bounds on columns.");
    }
}

Session::Session()
{}

Session::Session(const std::string &db)
{
    if (!open(db)) {
        throw SqlException("Faild to open database " + db);
    }
}

bool Session::open(const std::string &db)
{
    sqlite3 *tmp = nullptr;
    int r = sqlite3_open(db.c_str(), &tmp);

    if (r != SQLITE_OK) {
        return false;
    }

    this->db = std::shared_ptr<sqlite3>(tmp, sqlite3_close);
    return true;
}

Statement Session::prepare(const std::string &query)
{
    sqlite3_stmt *st = nullptr;
    int r = sqlite3_prepare_v2(db.get(), query.c_str(), -1, &st, nullptr);

    if (r != SQLITE_OK) {
        throw SqlException("Faild to prepare statement: " + query + ".");
    }

    return Statement(db, st);
}

i64 Session::lastRowInsertRowId()
{
    return sqlite3_last_insert_rowid(db.get());
}

void Session::operator<< (const std::string &query)
{
    auto s = prepare(query);

    if (s.step() != Sql::DONE) {
        throw SqlException("Query wasn't done after one step..");
    }
}

} /* Eater */

#undef CHECK_FOR_GET
