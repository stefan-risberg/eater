#include "eater/tag_table.hpp"

#include <format.h>

namespace eater
{

const str tag_table_t::tbl_tags      = "tags";
const str tag_table_t::col_id        = "id";
const str tag_table_t::col_name      = "name";

tag_table_t::tag_table_t()
{}

void tag_table_t::init(shared_session_t &s)
{
    _sql = s;
    *_sql << fmt::format(
        "create table if not exists {} ("
        "{} integer primary key,"
        "{} text not null",
        tbl_tags,
        col_id,
        col_name);


    LOGG_MESSAGE("Initialized: " << E_MAGENTA(tbl_tags) << ".");
}

void tag_table_t::insert(tag_t &tag, bool safe)
{
    if (safe) {
        if (exists(tag)) {
            throw exists_already("Tag exists in table: " + tag.name() + ".");
        } else if (exists(tag.id())) {
            throw exists_already("Tag with id: "
                                 + std::to_string(tag.id())
                                 + " exists already.");
        }
    }

    if (tag.id() == -1) {
        tag.id(_sql->last_index(tbl_tags, col_id) + 1);
    }

    *_sql << fmt::format(
        "insert into {} ({}, {}) values ({}, '{}');",
        tbl_tags,
        col_id,
        col_name,
        tag.id(),
        tag.name());
}

void tag_table_t::remove(tag_t &tag)
{
    if (tag.id() < 0) {
        throw std::invalid_argument("tag.id() < 0");
    }

    *_sql << fmt::format(
        "delete from {} where {}={};",
        tbl_tags,
        col_id,
        tag.id());
}

void tag_table_t::update(tag_t &tag)
{
    if (tag.id() < 0) {
        throw std::invalid_argument("tag.id() < 0");
    }

    *_sql << fmt::format(
        "update {} set {}='{}';",
        tbl_tags,
        col_id,
        tag.id());
}

tag_t tag_table_t::find(const id_t &tag) const
{
    tag_t t;
    auto st = _sql->prepare(fmt::format(
            "select {0} from {1} where {0}={2};",
            col_id,
            tbl_tags,
            tag));

    if (st.step() == sql::ROW) {
        t.id(tag);
        t.name(st.get_str(0));

        return t;
    }

    throw not_found("Did not find a tag with id: "
                    + std::to_string(tag)
                    + ".");
}

bool tag_table_t::exists(const id_t &tag) const
{
    if (tag < 0) {
        throw std::invalid_argument("tag < 0");
    }

    auto st = _sql->prepare(fmt::format(
            "select count({0}) from {1} where {0}={2};",
            col_id,
            tbl_tags,
            tag));


    if (st.step() == sql::ROW) {
        if (st.get_int(0) > 0) {
            return true;
        }
    }

    return false;
}

bool tag_table_t::exists(const tag_t &tag) const
{
    if (tag.id() < 0) {
        throw std::invalid_argument("tag < 0");
    }

    auto st = _sql->prepare(fmt::format(
            "select count({0}) from {1} where {2}='{3}' and {0}={4};",
            col_id,
            tbl_tags,
            col_name,
            tag.name(),
            tag.id()));

    if (st.step() == sql::ROW) {
        if (st.get_int(0) > 0) {
            return true;
        }
    }

    return false;
}

str tag_table_t::name() const
{
    return tbl_tags;
}

} /* eater */
