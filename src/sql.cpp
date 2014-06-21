#include "eater/sql.hpp"
#include "format.h"

namespace Eater
{
    Sql::Sql() {}

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
        fmt::Writer w;
        w.Format("select count(*) from sqlite_master where type='table' and "
                  "name='{}';") << tbl_name;

        bool tbl_exists = false;

        std::function<void(sqlite3_stmt*)> user_prog = [&] (sqlite3_stmt *st) {
            int ret = sqlite3_step(st);

            if (ret == SQLITE_DONE) {
                LOGG_MESSAGE("No table " << "fisk" << " found.");
                tbl_exists = false;
            } else if (ret == SQLITE_ROW) {
                ret = sqlite3_column_int(st, 0);

                tbl_exists = ret == 1;
            }
        };

        assert(prepare(w.str(), user_prog));

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
        std::function<void()> user_prog = [&] () {
            auto r = step();

            if (r != DONE) {
                LOGG_ERROR("Faild to create table. Step ret code: " << E_MAGENTA(r));
                created_table = false;
            } else {
                LOGG_MESSAGE("Created table: " << tbl_name);
                created_table = true;
            }
        };

        assert(prepare(w.str(), user_prog));

        return true;
    }

    bool Sql::select(const std::string &what,
                     const std::string &from,
                     const std::string &were)
    {
        fmt::Writer w;
        w.Format("select {} from {} where {};");

        return 0;
    }



    bool Sql::prepare(const std::string &querry,
                      std::function<void(sqlite3_stmt*)> &func)
    {
        int r = sqlite3_prepare_v2(sql_db.get(),
                                   querry.c_str(),
                                   -1,
                                   &st,
                                   nullptr);

        if (r != SQLITE_OK) {
            LOGG_ERROR("Faild to prepare statement:\n" << querry);
            return false;
        }

        func(st);
        sqlite3_finalize(st);
        st = nullptr;

        return true;
    }


} /* Eater
 */ 
