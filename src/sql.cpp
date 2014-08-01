#include "eater/sql.hpp"
#include "format.h"
#include <string>

namespace Eater
{

bool Sql::open(const std::string &location)
{
    sqlite3 *tmp = nullptr;
    int r = sqlite3_open(location.c_str(), &tmp);

    if (r != SQLITE_OK) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        LOGG_ERROR("Failed to open database: " << E_MAGENTA(location));

        return false;
    }

    LOGG_MESSAGE("Opened database: " << E_MAGENTA(location));
    sql_db = shared_sqlite3(tmp, sqlite3_close);

    return true;
}

bool Sql::tableExists(const std::string &tbl_name)
{

    fmt::Writer where;
    bool tbl_exists = false;

    where.Format("type='table' and name='{}'") << tbl_name;

    std::function<void()> func = [&]() {
        auto ret = step();

        if (ret == DONE) {
            LOGG_MESSAGE("No table " << tbl_name << " found.");
            tbl_exists = false;
        } else if (ret == ROW) {
            auto amount = columnInt(0);

            tbl_exists = amount == 1;
        } else {
            LOGG_ERROR(__PRETTY_FUNCTION__ << "Error after step.");

            tbl_exists = false;
        }
    };

    if (!select("sqlite_master", "count(*)", where.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return tbl_exists;
}

bool Sql::createTable(const std::string &tbl_name,
                      const str_vec &col_names,
                      const str_vec &col_types)
{
    if (col_names.size() != col_types.size()) {
        LOGG_ERROR("Wrong number of elements in col_names and col_types");
        return false;
    }

    fmt::Writer w;
    w.Format("create table {} (") << tbl_name;

    int col_amount = col_names.size();

    for (int i = 0; i < col_amount; i++) {
        w.Format("{} {}") << col_names[i] << col_types[i];

        if (i + 1 == col_amount) {
            w << ");";
        } else {
            w << ", ";
        }
    }

    bool created_table = false;
    std::function<void()> user_prog = [&]() {
        auto r = step();

        if (r != DONE) {
            LOGG_ERROR(
                "Faild to create table. Step ret code: " << E_MAGENTA(r));
            created_table = false;
        } else {
            LOGG_MESSAGE("Created table: " << tbl_name);
            created_table = true;
        }
    };

    if (!prepare(w.str(), user_prog)) {
        return false;
    }

    return created_table;
}

bool Sql::select(const std::string &tbl,
                 const std::string &what,
                 const std::string &where,
                 std::function<void()> &func)
{
    fmt::Writer w;
    w.Format("select {} from {} where {};") << what << tbl << where;

    if (!prepare(w.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return true;
}

bool Sql::select(const std::string &tbl,
                 const std::string &what,
                 std::function<void()> &func)
{
    fmt::Writer w;
    w.Format("select {} from {};") << what << tbl;

    if (!prepare(w.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return true;
}

bool Sql::update(const std::string &tbl,
                 const std::string &to,
                 const std::string &where)
{
    fmt::Writer w;
    w.Format("update {} set {} where {};") << tbl << to << where;

    bool ret = false;
    std::function<void()> func = [this, &ret]() {
        if (step() == DONE) {
            ret = true;
        } else {
            ret = false;
        }
    };

    if (!prepare(w.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
        return false;
    }

    return ret;
}

bool Sql::insert(const std::string &tbl,
                 const std::string &col_names,
                 const std::string &col_values)
{
    fmt::Writer w;
    w.Format("insert into {} ({}) values ({});") << tbl << col_names
                                                 << col_values;
    bool ret = false;

    if (!prepare(w.str(), [&]() {
             auto s = step();
             if (s != DONE) {
                 LOGG_ERROR("Failed to insert to table "
                            << tbl << ". Error code: " << s);
                 ret = false;
             } else {
                 ret = true;
             }
         })) {
        return false;
    }

    LOGG_MESSAGE("Insert into: " << E_MAGENTA(tbl));

    return ret;
}

DB_Driver::Status Sql::step()
{
    if (st == nullptr) {
        LOGG_ERROR("Tried to get column on a non-existant statement.");
        return ERROR;
    }

    auto r = sqlite3_step(st);

    switch (r) {
        case SQLITE_OK:
            return OK;
        case SQLITE_ERROR:
            return ERROR;
        case SQLITE_BUSY:
            return BUSY;
        case SQLITE_FULL:
            return FULL;
        case SQLITE_ROW:
            return ROW;
        case SQLITE_DONE:
            return DONE;
        default:
            return OTHER;
    }
}

bool Sql::prepare(const std::string &querry, const std::function<void()> &func)
{
    int r = sqlite3_prepare_v2(sql_db.get(), querry.c_str(), -1, &st, nullptr);

    if (r != SQLITE_OK) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << "Faild to prepare statement:\n"
                                       << querry);
        return false;
    }

    func();
    sqlite3_finalize(st);
    st = nullptr;

    return true;
}

int Sql::columnInt(int col)
{
    if (st == nullptr) {
        LOGG_ERROR("Tried to get column on a non-existant statement.");
        return 0;
    }

    int r = sqlite3_column_int(st, col);
    return r;
}

std::string Sql::columnStr(int col)
{
    if (st == nullptr) {
        LOGG_ERROR("Tried to get column on a non-existant statement.");
        return 0;
    }

    return std::string(
        reinterpret_cast<const char *>(sqlite3_column_text(st, col)));
}

double Sql::columnDouble(int col)
{
    if (st == nullptr) {
        LOGG_ERROR("Tried to get column on a non-existant statement.");
        return 0;
    }

    return sqlite3_column_double(st, col);
}

int Sql::getLastInsertRowId()
{
    return sqlite3_last_insert_rowid(sql_db.get());
}
} /* Eater
 */
