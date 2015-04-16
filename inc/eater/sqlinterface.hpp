#ifndef EATER_SQL_INTERFACE_HPP_
#define EATER_SQL_INTERFACE_HPP_

#include <sqlite3.h>
#include <memory>
#include <string>
#include <exception>

#include "eater/common.hpp"

namespace Eater
{

class SqlException : public std::exception {
 public:
    explicit SqlException(const std::string &msg)
    {
        this->msg = msg;
    }

    virtual const char* what() const throw()
    {
        return msg.c_str();
    }

 private:
    std::string msg;
};

namespace Sql
{

enum Status {
    OK,
    ERROR,
    BUSY,
    FULL,
    ROW,
    DONE,
    OTHER
};

enum Type {
    INTEGER,
    DOUBLE,
    TEXT,
    BLOB,
    NONE
};

} /* sql */
class Session;

/**
 * A prepared sql statement.
 */
class Statement {
    friend class Session;
 private:
    /**
     * Default constructor. It takes over st.
     *
     * \param db - Pointer to database that owns the statement.
     * \param st - A statement.
     */
    Statement(std::shared_ptr<sqlite3> &db, sqlite3_stmt *st);

 public:

    /**
     * Cleans up the statement.
     */
    ~Statement();

    /**
     * Steps the statement by one step.
     */
    Sql::Status step();

    /**
     * Gets the type of a row.
     *
     * \param col - Column to get type of.
     * \return The type of the column col.
     */
    Sql::Type getType(i32 col);

    /**
     * Get the int from column col.
     * \param col - Column to query.
     * \return integer containd in the column.
     */
    i32 getInt(i32 col);

    /**
     * Get the double from column col.
     * \param col - Column to query.
     * \return double containd in the column.
     */
    f64 getDouble(i32 col);

    /**
     * Get the text from column col.
     * \param col - Column to query.
     * \return text containd in the column.
     */
    str getStr(i32 col);

 private:
    sqlite3_stmt *st = nullptr;
    Sql::Status last_status = Sql::OK;
    i32 col_count = 0;
    std::shared_ptr<sqlite3> db;

    inline void validateBeforeGet(i32 col);
};

class Session {
 public:
    Session();
    Session(const std::string &db);

    bool open(const std::string &db);

    Statement prepare(const std::string &query);
    i64 lastRowInsertRowId();

    void operator<< (const std::string &query);

 private:
    std::shared_ptr<sqlite3> db = nullptr;
};

} /* Eater */

#endif /* end of include guard: EATER_SQL_INTERFACE_HPP_ */

