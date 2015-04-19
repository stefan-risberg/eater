#include "eater/sqlinterface.hpp"

namespace eater
{

statement_t::statement_t(std::shared_ptr<sqlite3> &db, sqlite3_stmt *st)
{
    if (st == nullptr) {
        throw sql_error("Tried to initialize statement with null.");
    }

    this->st = st;
    col_count = sqlite3_column_count(st);
    this->db = db;
}

statement_t::~statement_t()
{
    sqlite3_finalize(st);
}

sql::status_t statement_t::step()
{
    if (st == nullptr) {
        return sql::ERROR;
    }

    auto r = sqlite3_step(st);

    switch(r) {
    case SQLITE_OK: last_status = sql::OK; break;
    case SQLITE_ERROR: last_status = sql::ERROR; break;
    case SQLITE_BUSY: last_status = sql::BUSY; break;
    case SQLITE_FULL: last_status = sql::FULL; break;
    case SQLITE_ROW: last_status = sql::ROW; break;
    case SQLITE_DONE: last_status = sql::DONE; break;
    default: last_status = sql::OTHER;
    }

    return last_status;
}

sql::type_t statement_t::get_type(i32 col)
{
    val_before_get(col);

    switch(sqlite3_column_type(st, col)) {
    case SQLITE_INTEGER: return sql::INTEGER;
    case SQLITE_FLOAT: return sql::DOUBLE;
    case SQLITE_TEXT: return sql::TEXT;
    case SQLITE_BLOB: return sql::BLOB;
    default: return sql::NONE;
    }
}

i32 statement_t::get_int(i32 col)
{
    val_before_get(col);
    return sqlite3_column_int(st, col);
}

f64 statement_t::get_double(i32 col)
{
    val_before_get(col);
    return sqlite3_column_double(st, col);
}

std::string statement_t::get_str(i32 col)
{
    val_before_get(col);
    return std::string(
        reinterpret_cast<const char *> (sqlite3_column_text(st, col)));
}

void statement_t::val_before_get(i32 col)
{
    if (st == nullptr) {
        throw sql_error("No prepared statement.");
    }

    if (last_status != sql::ROW) {
        throw sql_error("No row to extract data from.");
    }

    if (col >= col_count) {
        throw sql_error("Out of bounds on columns.");
    }
}

session_t::session_t()
{}

session_t::session_t(const std::string &db)
{
    if (!open(db)) {
        throw sql_error("Faild to open database " + db);
    }
}

bool session_t::open(const std::string &db)
{
    sqlite3 *tmp = nullptr;
    int r = sqlite3_open(db.c_str(), &tmp);

    if (r != SQLITE_OK) {
        return false;
    }

    this->db = std::shared_ptr<sqlite3>(tmp, sqlite3_close);
    return true;
}

statement_t session_t::prepare(const std::string &query)
{
    sqlite3_stmt *st = nullptr;
    int r = sqlite3_prepare_v2(db.get(), query.c_str(), -1, &st, nullptr);

    if (r != SQLITE_OK) {
        throw sql_error("Faild to prepare statement: " + query + ".");
    }

    return statement_t(db, st);
}

i64 session_t::lastRowInsertRowId()
{
    return sqlite3_last_insert_rowid(db.get());
}

void session_t::operator<< (const std::string &query)
{
    auto s = prepare(query);

    if (s.step() != sql::DONE) {
        throw sql_error("Query wasn't done after one step..");
    }
}

} /* eater */

