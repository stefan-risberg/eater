#ifndef EATER_TAGS_HPP_
#define EATER_TAGS_HPP_

#include "eater/common.hpp"

namespace eater
{
/**
 * Holds a tag with its id.
 */
class tag_t {
 private:
    id_t _id;
    str _name;

 public:
    tag_t();
    tag_t(const str &name);
    tag_t(id_t id, const str &name);

    void id(id_t id);
    id_t id() const;

    void name(const str &name);
    str name() const;

    bool operator==(const tag_t &t) const;
};

/**
 * Holds only unique tags.
 */
class tag_vec
{
   private:
      std::vector<tag_t> _tags;

   public:
      typedef std::vector<tag_t>::iterator iterator;
      typedef std::vector<tag_t>::const_iterator const_iterator;

   public:
    /**
     * Default constructor.
     */
    tag_vec();

    /**
     * Copy constructor.
     *
     * \param tags To copy.
     */
    tag_vec(const tag_vec &tags);

    /**
     * Move constructor.
     */
    tag_vec(tag_vec &&tags);

    /**
     * Checks if a tag exists.
     *
     * \param tag tag to find.
     * \return True if found else false.
     */
    bool exists(const str &name);

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
    bool add(const tag_t &tag);

    /**
     * Removes a tag.
     *
     * \param tag Tag to remove
     * \return Ture if tag was removed, else false.
     */
    bool remove(const tag_t &tag);

    /**
     * Removes a tag.
     *
     * \param it Iterator position.
     * \return Iterator following the last removed element.
     */
    tag_vec::iterator remove(tag_vec::iterator &it);

    /**
     * Gets an iterator.
     *
     * \return Gets an iterator at the beginning of tags.
     */
    iterator begin();

    /**
     * Gets an iterator.
     *
     * \return Gets an iterator at the beginning of tags.
     */
    const_iterator begin() const;

    /**
     * Gets an iterator.
     *
     * \return Gets an interator at the end of the tags.
     */
    iterator end();

    /**
     * Gets an iterator.
     *
     * \return Gets an interator at the end of the tags.
     */
    const_iterator end() const;

    /**
     * Creates a string representation of all tags.
     *
     * \return String representation of tags.
     */
    str to_str() const;

    tag_vec &operator=(const tag_vec &t);
};
} /* eater */

std::ostream &operator<<(std::ostream &os, const eater::tag_vec &tags);

#endif /* end of include guard: EATER_TAGS_HPP_ */

