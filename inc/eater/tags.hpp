#ifndef TAGS_HPP_
#define TAGS_HPP_

#include "eater/common.hpp"

namespace Eater
{
    /**
     * Holds only unique tags.
     */
    class Tags
    {
    private:
        tags_t *_tags = nullptr;

    public:
        /**
         * Takes ownership of a tag vector.
         *
         * \param[in] tags Vector of tags.
         * \param valid True if tags doesn't contain duplicates.  
         */
        Tags(tags_t *tags, bool valid = true);

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
         * Default destructor.
         */
        ~Tags();

        /**
         * Checks if a tag exists.
         *
         * \param tag Tag to find.
         * \return True if found else false. 
         */
        bool find(const std::string &tag);

        /**
         * Adds a tag.
         *
         * Will not add duplicated.
         *
         * \param tag Tag to add.
         * \return If tag exists, false. Else true. 
         */
        bool addTag(const std::string &tag);

        /**
         * Adds tags.
         *
         * Will not add duplicates.
         *
         * \param tags Tags to be added.
         * \return If one, some or all are already presant, false. Else true. 
         */
        bool addTags(const tags_t &tags);

        /**
         * Removes a tag.
         *
         * \param tag Tag to remove
         * \return Ture if tag was removed, else false. 
         */
        bool removeTag(const std::string &tag);

        /**
         * Removes a tag.
         *
         * \param it Iterator position.
         * \return Iterator following the last removed element.
         */
        tags_t::iterator removeTag(tags_t::iterator &it);

        /**
         * Removes tags.
         *
         * \param tags Tags to be removed.
         * \return false if not all tags was removed, else false. 
         */
        bool removeTags(const tags_t &tags);

        /**
         * Gets an iterator.
         *
         * \return Gets an iterator at the beginning of tags.
         */
        tags_t::iterator begin();

        /**
         * Gets an iterator.
         *
         * \return Gets an iterator at the beginning of tags.
         */
        tags_t::const_iterator begin() const;
        
        /**
         * Gets an iterator.
         *
         * \return Gets an interator at the end of the tags.
         */
        tags_t::iterator end();

        /**
         * Gets an iterator.
         *
         * \return Gets an interator at the end of the tags.
         */
        tags_t::const_iterator end() const;
    };
} /* Eater */ 

#endif /* end of include guard: TAGS_HPP_ */

