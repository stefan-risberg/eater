#include "eater/tags.hpp"
#include <format.h>

namespace eater
{
tag_t::tag_t() :
    _id(-1),
    _name("")
{}

tag_t::tag_t(const str &name) :
    _id(-1),
    _name(name)
{}

tag_t::tag_t(id_t id, const str &name) :
    _id(id),
    _name(name)
{}

void tag_t::id(id_t id)
{
    _id = id;
}

id_t tag_t::id() const
{
    return _id;
}

void tag_t::name(const str &name)
{
    _name = name;
}

str tag_t::name() const
{
    return _name;
}

bool tag_t::operator==(const tag_t &t) const
{
    if (this->id () == t.id() && this->name() == t.name()) {
        return true;
    }
    return false;
}

tag_vec::tag_vec()
{}

tag_vec::tag_vec(const tag_vec &tags) : _tags(tags._tags)
{}

tag_vec::tag_vec(tag_vec &&tags) : _tags(std::move(tags._tags))
{}

bool tag_vec::exists(const str &name)
{
    for (auto &it : _tags) {
        if (it.name() == name) {
            return true;
        }
    }

    return false;
}

bool tag_vec::exists(id_t id)
{
    for (auto &it : _tags) {
        if (it.id() == id) {
            return true;
        }
    }

    return false;
}

bool tag_vec::add(const tag_t &tag)
{
    if (tag.id() == -1) {
        return false;
    }

    for (auto it = begin(); it != end(); it++) {
        if (*it == tag) {
            return false;
        }
    }

    _tags.push_back(tag);
    return true;
}

bool tag_vec::remove(const tag_t &tag)
{
    for (auto it = begin(); it != end(); it++) {
        if (*it == tag) {
            _tags.erase(it);
            return true;
        }
    }

    return false;
}

tag_vec::iterator tag_vec::remove(tag_vec::iterator &it)
{
    return _tags.erase(it);
}

tag_vec::iterator tag_vec::begin()
{
    return _tags.begin();
}

tag_vec::const_iterator tag_vec::begin() const
{
    return _tags.cbegin();
}

tag_vec::iterator tag_vec::end()
{
    return _tags.end();
}

tag_vec::const_iterator tag_vec::end() const
{
    return _tags.cend();
}

str tag_vec::to_str() const
{
    fmt::Writer w;
    bool first = true;

    w.Format("[");

    for (auto &it : _tags) {
        if (first) {
            w.Format("{}: {}")
                << std::to_string(it.id())
                << it.name();
            first = false;
        } else {
            w.Format(", {}: {}")
                << std::to_string(it.id())
                << it.name();
        }
    }

    w.Format("]");

    return w.str();
}

tag_vec &tag_vec::operator=(const tag_vec &t)
{
    _tags = t._tags;

    return *this;
}
} /* eater */

std::ostream &operator<<(std::ostream &os, const eater::tag_vec &tag_vec)
{
    return os << tag_vec.to_str();
}

