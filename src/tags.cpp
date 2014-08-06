#include "eater/tags.hpp"

namespace Eater
{
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

bool Tags::find(const std::string &tag)
{
    for (auto &it : _tags) {
        if (it == tag) {
            return true;
        }
    }

    return false;
}

bool Tags::addTag(const std::string &tag)
{
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
    bool found_dup = false;

    for (auto it = tags.begin(); it != tags.end(); it++) {
        bool r = addTag(*it);

        if (!r) {
            found_dup = true;
        }
    }

    return !found_dup;
}

bool Tags::removeTag(const std::string &tag)
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
    std::string str = "";
    for (auto it = begin(); it != end(); it++) {
        str += *it;
        if (it + 1 != end()) {
            str += ',';
        }
    }

    return str;
}

// TODO: Make syntax check on tags string (14.03.16 - steffenomak)
void Tags::fromString(const std::string &tags)
{
    _tags.clear();

    std::string tag = "";

    for (auto it = tags.begin(); it != tags.end(); it++) {
        if (*it == ',') {
            addTag(tag);
            tag = "";
        } else {
            tag += *it;
        }
    }
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

std::istream &operator>>(std::istream &is, Eater::Tags &tags)
{
    std::string str;
    is >> str;

    tags.fromString(str);

    return is;
}
