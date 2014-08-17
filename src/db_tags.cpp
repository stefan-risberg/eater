#include "eater/db_tags.hpp"
#include "eater/db.hpp"
#include "format.h"
#include <cassert>
#include <vector>
#include <string>

namespace Eater
{
const char *DB_Tags::col_id = "id";

const char *DB_Tags::tbl_tags = "tags";
const char *DB_Tags::tbl_fooditem_tags = "fooditem_tags";

const char *DB_Tags::col_tags_id = "tag_id";
const char *DB_Tags::col_tags_name = "name";
const char *DB_Tags::col_fooditem_id = "fooditem_id";

bool DB_Tags::initTagsTable()
{
    if (db->tableExists(tbl_tags)) {
        LOGG_MESSAGE(tbl_tags << " exists.");
    } else {
        std::vector<std::string> col_names = {
            col_id,
            col_tags_name
        };

        std::vector<std::string> col_types = {
            "integer primary key",
            "text not null"
        };

        LOGG_MESSAGE("Creating table " << tbl_tags << ".");

        if (!db->createTable(tbl_tags, col_names, col_types)) {
            LOGG_ERROR(__PRETTY_FUNCTION__);

            return false;
        }
    }

    return true;
}

bool DB_Tags::initFooditemTagsTable()
{
    if (db->tableExists(tbl_fooditem_tags)) {
        LOGG_MESSAGE(tbl_fooditem_tags << " exists.");
    } else {
        std::vector<std::string> col_names = {
            col_id,
            col_tags_id,
            col_fooditem_id
        };

        std::vector<std::string> col_types = {
            "integer primary key",
            "integer not null",
            "integer not null"
        };

        LOGG_MESSAGE("Try to create table " << tbl_fooditem_tags << ".");

        if (!db->createTable(tbl_fooditem_tags, col_names, col_types)) {
            LOGG_ERROR(__PRETTY_FUNCTION__);

            return false;
        }
    }

    return true;
}

DB_Tags::DB_Tags(std::shared_ptr<DB_Driver> &db) : TableHandler(db)
{
}

DB_Tags::~DB_Tags()
{
    close();
}

bool DB_Tags::init()
{
    if (!initTagsTable() && !initFooditemTagsTable()) {
        LOGG_ERROR(__PRETTY_FUNCTION__);

        return false;
    }

    return true;
}

void DB_Tags::close()
{
    if (db != nullptr) {
        db.reset();
    }
}

bool DB_Tags::tagExists(const std::string &tag) const
{
    fmt::Writer where;
    bool found = false;

    where.Format("{}='{}'") << col_tags_name << tag;

    std::function<void ()> func = [&]() {
        auto s = db->step();

        if (s == DB_Driver::ROW) {
            found = true;
        } else {
            found = false;
        }
    };

    CHECK_RESULT(db->select(tbl_tags, "*", where.str(), func));

    return found;
}

int DB_Tags::createTag(const std::string &tag)
{
    fmt::Writer name, value;

    name.Format("{}") << col_tags_name;
    value.Format("'{}'") << tag;

    if (!db->insert(tbl_tags, name.str(), value.str())) {
        return -1;
    }

    return db->getLastInsertRowId();
}

std::string DB_Tags::getTag(id_t id) const
{
    fmt::Writer where;
    std::string tag = "";

    where.Format("{}={}") << col_id << id;

    std::function<void()> func = [&] () {
        auto s = db->step();

        if (s == DB_Driver::ROW) {
            tag = db->columnStr(0);
        }
    };

    if (!db->select(tbl_tags, col_tags_name, where.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__);
    }

    return tag;
}

Tags DB_Tags::getTags(id_t fi_id)
{
    fmt::Writer where;
    Tags tags;
    std::vector<int> tag_ids;

    where.Format("{}={}") << col_fooditem_id << fi_id;

    std::function<void()> func = [&] () {
        while (db->step() == DB_Driver::ROW) {
            tag_ids.push_back(db->columnInt(0));
        }
    };

    if (!db->select(tbl_fooditem_tags, col_tags_id, where.str(), func)) {
        LOGG_ERROR(__PRETTY_FUNCTION__ << " - faild to select all tags.");
        return tags;
    }

    for (auto it = tag_ids.begin(); it != tag_ids.end(); it++) {
        tags.addTag(getTag(*it));
    }

    return tags;
}

} /* Eater */
