#ifndef EATER_SQL_INTERFACE_HPP_
#define EATER_SQL_INTERFACE_HPP_

#include <sqlite3.h>
#include <memory>
#include <string>
#include <exception>

#include "eater/common.hpp"

namespace eater
{

class sql_exception : public std::exception {
 public:
    explicit sql_exception(const str &msg)
    {
        this->_msg = msg;
    }

    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }

 private:
    str _msg;
};

namespace sql
{

enum status_t {
    OK,
    ERROR,
    BUSY,
    FULL,
    ROW,
    DONE,
    OTHER
};

enum type_t {
    INTEGER,
    DOUBLE,
    TEXT,
    BLOB,
    NONE
};

} /* sql */
class session_t;

/**
 * A prepared sql statement.
 */
class statement_t {
    friend class session_t;
 private:
    /**
     * Default constructor. It takes over st.
     *
     * \param db - Pointer to database that owns the statement.
     * \param st - A statement.
     */
    statement_t(std::shared_ptr<sqlite3> &db, sqlite3_stmt *st);

 public:

    /**
     * Cleans up the statement.
     */
    ~statement_t();

    /**
     * Steps the statement by one step.
     */
    sql::status_t step();

    /**
     * Gets the type of a row.
     *
     * \param col - Column to get type of.
     * \return The type of the column col.
     */
    sql::type_t get_type(i32 col);

    /**
     * Get the int from column col.
     * \param col - Column to query.
     * \return integer containd in the column.
     */
    i32 get_int(i32 col);

    /**
     * Get the double from column col.
     * \param col - Column to query.
     * \return double containd in the column.
     */
    f64 get_double(i32 col);

    /**
     * Get the text from column col.
     * \param col - Column to query.
     * \return text containd in the column.
     */
    str get_str(i32 col);

 private:
    sqlite3_stmt *st = nullptr;
    sql::status_t last_status = sql::OK;
    i32 col_count = 0;
    std::shared_ptr<sqlite3> db;

    inline void val_before_get(i32 col);
};

class session_t {
 public:
    session_t();
    session_t(const str &db);

    bool open(const str &db);

    statement_t prepare(const str &query);
    i64 lastRowInsertRowId();

    void operator<< (const str &query);

 private:
    std::shared_ptr<sqlite3> db = nullptr;
};

} /* eater */

#endif /* end of include guard: EATER_SQL_INTERFACE_HPP_ */

