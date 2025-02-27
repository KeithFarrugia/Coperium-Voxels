#ifndef UNORDERED_MAP_DATASTRUCTURE_H
#define UNORDERED_MAP_DATASTRUCTURE_H

#include "IDataStructure.h"
#include <unordered_map>

// The UnorderedMapDataStructure provides a concrete implementation of IDataStructure
// using std::unordered_map. It returns a pointer to the mapped value from Insert
// and provides begin() and end() methods for range-based iteration.
template <typename id_type, typename data_type>
class UnorderedMapDataStructure : public IDataStructure<id_type, data_type> {
private:
    std::unordered_map<id_type, data_type> map;

public:
    virtual ~UnorderedMapDataStructure() override = default;

    /* ============================================================================
     * --------------------------- Insert
     * Inserts a key-value pair into the unordered_map. If the key already exists,
     * its value is overwritten. Returns a pointer to the stored data.
     *
     * ------ Parameters ------
     * id:    The key used for indexing.
     * data:  The data to insert.
     *
     * ------ Returns --------
     * Pointer to the data stored at the key.
     * ============================================================================
     */
    virtual data_type* Insert(const id_type& id, const data_type& data) override {
        auto& element = map[id];  // Inserts a default element if id is not present.
        element = data;           // Assign the provided data.
        return &element;
    }

    /* ============================================================================
     * --------------------------- Remove
     * Removes the element with the given key from the unordered_map.
     *
     * ------ Parameters ------
     * id:  The key identifying the element to remove.
     * ============================================================================
     */
    virtual void Remove(const id_type& id) override {
        map.erase(id);
    }

    /* ============================================================================
     * --------------------------- Find
     * Searches for the element with the given key and returns a pointer to its data.
     *
     * ------ Parameters ------
     * id:  The key to search for.
     *
     * ------ Returns --------
     * Pointer to the data if found; nullptr otherwise.
     * ============================================================================
     */
    virtual data_type* Find(const id_type& id) const override {
        auto it = map.find(id);
        return (it != map.end()) ? const_cast<data_type*>(&it->second) : nullptr;
    }

    /* ============================================================================
     * --------------------------- Clear
     * Clears the entire unordered_map.
     * ============================================================================
     */
    virtual void Clear() override {
        map.clear();
    }

    // --------------------------------- CUSTOM ITERATOR
    class Iterator {
    public:
        /* ============================================================================
         * --------------------------- Iterator
         * Constructor that initializes the iterator with the underlying unordered_map iterator.
         * ------ Parameters ------
         * it:    Underlying unordered_map iterator.
         * ============================================================================
         */
        Iterator(typename std::unordered_map<id_type, data_type>::iterator it) : it(it) {}

        /* ============================================================================
         * --------------------------- operator*
         * Dereferences the iterator to access the current element as a pair.
         * ------- Returns --------
         * A std::pair containing references to the key (first) and data (second).
         * ============================================================================
         */
        std::pair<id_type&, data_type&> operator*() {
            // Cast away constness from the key to match the AVL tree interface.
            return { const_cast<id_type&>(it->first), it->second };
        }

        /* ============================================================================
         * --------------------------- operator++
         * Advances the iterator to the next element.
         * ------- Returns --------
         * Reference to the iterator after it has been incremented.
         * ============================================================================
         */
        Iterator& operator++() {
            ++it;
            return *this;
        }

        /* ============================================================================
         * --------------------------- operator!=
         * Compares two iterators for inequality.
         * ------ Parameters ------
         * other:   Another iterator to compare with.
         * ------- Returns --------
         * True if the iterators are not equal; false otherwise.
         * ============================================================================
         */
        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

    private:
        typename std::unordered_map<id_type, data_type>::iterator it;
    };

    /* ============================================================================
     * --------------------------- begin
     * Returns an iterator to the beginning of the unordered_map.
     * ------- Returns --------
     * An iterator for the beginning element.
     * ============================================================================
     */
    Iterator begin() {
        return Iterator(map.begin());
    }

    /* ============================================================================
     * --------------------------- end
     * Returns an iterator to the end of the unordered_map.
     * ------- Returns --------
     * An iterator representing the end.
     * ============================================================================
     */
    Iterator end() {
        return Iterator(map.end());
    }
};

#endif // UNORDERED_MAP_DATASTRUCTURE_H
