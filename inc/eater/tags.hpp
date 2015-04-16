#ifndef EATER_TAGS_HPP_
#define EATER_TAGS_HPP_

#include "eater/common.hpp"

namespace Eater
{
/**
 * Holds a tag with its id.
 */
class Tag {
 private:
    id_t _id;
    std::string _name;

 public:
    Tag();
    Tag(const std::string &name);
    Tag(id_t id, const std::string &name);

    void id(id_t id);
    id_t id() const;

    void name(const std::string &name);
    std::string name() const;

    bool operator==(const Tag &t) const;
};

typedef std::vector<Tag> tags_vec;

/**
 * Holds only unique tags.
 */
class Tags
{
   private:
    tags_vec _tags;

   public:
    /**
     * Takes ownership of a tag vector.
     *
     * \param[in] tags Vector of tags.
     * \param valid True if tags doesn't contain duplicates.
     */
    Tags(tags_vec &&tags, bool valid = true);

    /**
     * Default constructor.
     */
    Tags();

    /**
     * Copy constructor.
     *
     * \param tags To copy.
     */
    Tags(const Tags &tags);

    /**
     * Move constructor.
     */
    Tags(Tags &&tags);

    /**
     * Checks if a tag exists.
     *
     * \param tag Tag to find.
     * \return True if found else false.
     */
    bool exists(const std::string &name);

    /**
     * Checks if a tag with id exists.
     *
     * \param id Id to search by.
     * \return True if found, else false.
     */
    bool exists(id_t id);

    /**
     * Adds a tag.
     *
     * Will not add duplicated.
     *
     * \param tag Tag to add.
     * \return If tag exists, false. Else true.
     */
    bool addTag(const Tag &tag);

    /**
     * Adds tags.
     *
     * Will not add duplicates.
     *
     * \param tags Tags to be added.
     * \return If all, some or one where added, true else false.
     */
    bool addTags(const tags_vec &tags);

    /**
     * Removes a tag.
     *
     * \param tag Tag to remove
     * \return Ture if tag was removed, else false.
     */
    bool removeTag(const Tag &tag);

    /**
     * Removes a tag.
     *
     * \param it Iterator position.
     * \return Iterator following the last removed element.
     */
    tags_vec::iterator removeTag(tags_vec::iterator &it);

    /**
     * Removes tags.
     *
     * \param tags Tags to be removed.
     * \return false if not all tags was removed, else false.
     */
    bool removeTags(const tags_vec &tags);

    /**
     * Gets an iterator.
     *
     * \return Gets an iterator at the beginning of tags.
     */
    tags_vec::iterator begin();

    /**
     * Gets an iterator.
     *
     * \return Gets an iterator at the beginning of tags.
     */
    tags_vec::const_iterator begin() const;

    /**
     * Gets an iterator.
     *
     * \return Gets an interator at the end of the tags.
     */
    tags_vec::iterator end();

    /**
     * Gets an iterator.
     *
     * \return Gets an interator at the end of the tags.
     */
    tags_vec::const_iterator end() const;

    /**
     * Creates a string representation of all tags.
     *
     * \return String representation of tags.
     */
    std::string toString() const;

    Tags &operator=(const Tags &t);
};
} /* Eater */

std::ostream &operator<<(std::ostream &os, const Eater::Tags &tags);

#endif /* end of include guard: EATER_TAGS_HPP_ */

