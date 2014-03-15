#include "eater/tags.hpp"

namespace Eater
{
    Tags::Tags(tags_t *tags, bool valid)
    {
        if (!valid) {
            for (size_t i = 0; i < tags->size(); i++) {
                for (size_t j = i + 1; j < tags->size(); j++) {
                    if (tags->at(i) == tags->at(j)) {
                        tags->erase(tags->begin() + j);
                        j--;
                    }
                }
            }
        }

        _tags = tags;
    }

    Tags::Tags()
    {
        _tags = new tags_t;
    }

    Tags::Tags(const Tags &tags)
    {
        _tags = new tags_t;
        for (auto it = tags.begin(); it != tags.end(); it++) {
            _tags->push_back(*it);
        }
    }

    Tags::~Tags()
    {
        if (_tags != nullptr) {
            delete _tags;
        }
    }

    bool Tags::find(const std::string &tag)
    {
        for (auto it = begin(); it != end(); it++) {
            if (*it == tag) {
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

        _tags->push_back(tag);
        return true;
    }

    bool Tags::addTags(const tags_t &tags)
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
                _tags->erase(it);
                return true;
            }
        }

        return false;
    }

    tags_t::iterator Tags::removeTag(tags_t::iterator &it)
    {
        return _tags->erase(it);
    }

    bool Tags::removeTags(const tags_t &tags)
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

    tags_t::iterator Tags::begin()
    {
        return _tags->begin();
    }

    tags_t::const_iterator Tags::begin() const
    {
        return _tags->cbegin();
    }

    tags_t::iterator Tags::end()
    {
        return _tags->end();
    }

    tags_t::const_iterator Tags::end() const
    {
        return _tags->cend();
    }
} /* Eater */ 
