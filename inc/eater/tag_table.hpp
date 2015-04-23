#ifndef EATER_TAGS_TABLE_HPP__
#define EATER_TAGS_TABLE_HPP__

#include "eater/common.hpp"
#include "eater/table_handler.hpp"
#include "eater/tags.hpp"
#include "eater/sqlinterface.hpp"

namespace eater
{

class tag_table_t : public table_handler_t<tag_t, id_t> {
 public:
    tag_table_t();
    void init(shared_session_t &s);

    void insert(tag_t &tag, bool safe = true);
    void remove(tag_t &tag);
    void update(tag_t &tag);

    tag_t find(const id_t &tag) const;

    bool exists(const id_t &tag) const;
    bool exists(const tag_t &tag) const;

    str name() const;

 private:
    shared_session_t _sql;

 public:
    static const str tbl_tags;
    static const str col_id;
    static const str col_name;
};

} /* eater */

#endif /* end of include guard: EATER_TAGS_TABLE_HPP__ */

