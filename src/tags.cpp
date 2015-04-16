#include "eater/tags.hpp"
#include <format.h>

namespace Eater
{
Tag::Tag() :
    _id(-1),
    _name("")
{}

Tag::Tag(const std::string &name) :
    _name(name)
{}

Tag::Tag(id_t id, const std::string &name) :
    _id(id),
    _name(name)
{}

void Tag::id(id_t id)
{
    _id = id;
}

id_t Tag::id() const
{
    return _id;
}

void Tag::name(const std::string &name)
{
    _name = name;
}

std::string Tag::name() const
{
    return _name;
}

bool Tag::operator==(const Tag &t) const
{
    if (this->id () == t.id() && this->name() == t.name()) {
        return true;
    }
    return false;
}

Tags::Tags(tags_vec &&tags, bool valid) : _tags(tags)
{
    if (!valid) {
        for (auto i = _tags.begin(); i != _tags.end(); i++) {
            for (auto j = i + 1; j != _tags.end(); j++) {
                if (*j == *i) {
                    _tags.erase(j);
                    j--;
                }
            }
        }
    }
}

Tags::Tags()
{
}

Tags::Tags(const Tags &tags) : _tags(tags._tags)
{
}

Tags::Tags(Tags &&tags) : _tags(std::move(tags._tags))
{
}

bool Tags::exists(const std::string &name)
{
    for (auto &it : _tags) {
        if (it.name() == name) {
            return true;
        }
    }

    return false;
}

bool Tags::exists(id_t id)
{
    for (auto &it : _tags) {
        if (it.id() == id) {
            return true;
        }
    }

    return false;
}

bool Tags::addTag(const Tag &tag)
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

bool Tags::addTags(const tags_vec &tags)
{
    bool added_one = false;

    for (auto &it : tags) {
        bool r = addTag(it);
        if (r) {
            added_one = true;
        }
    }

    return added_one;
}

bool Tags::removeTag(const Tag &tag)
{
    for (auto it = begin(); it != end(); it++) {
        if (*it == tag) {
            _tags.erase(it);
            return true;
        }
    }

    return false;
}

tags_vec::iterator Tags::removeTag(tags_vec::iterator &it)
{
    return _tags.erase(it);
}

bool Tags::removeTags(const tags_vec &tags)
{
    bool one_failed = false;

    for (auto it = tags.begin(); it != tags.end(); it++) {
        bool r = removeTag(*it);

        if (!r) {
            one_failed = true;
        }
    }

    return !one_failed;
}

tags_vec::iterator Tags::begin()
{
    return _tags.begin();
}

tags_vec::const_iterator Tags::begin() const
{
    return _tags.cbegin();
}

tags_vec::iterator Tags::end()
{
    return _tags.end();
}

tags_vec::const_iterator Tags::end() const
{
    return _tags.cend();
}

std::string Tags::toString() const
{
    fmt::Writer w;
    bool first = false;
    for (auto &it : _tags) {
        if (first) {
            w.Format("[{}: {}")
                << std::to_string(it.id())
                << it.name();
        } else {
            w.Format(", {}: {}")
                << std::to_string(it.id())
                << it.name();
        }
    }

    w.Format("]");

    return w.str();
}

Tags &Tags::operator=(const Tags &t)
{
    _tags = t._tags;

    return *this;
}
} /* Eater */

std::ostream &operator<<(std::ostream &os, const Eater::Tags &tags)
{
    return os << tags.toString();
}

