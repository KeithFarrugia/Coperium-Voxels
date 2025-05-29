#ifndef AVL_DATASTRUCTURE_H
#define AVL_DATASTRUCTURE_H

#include "IDataStructure.h"
#include "COIL/DataStructures/IndexedAvlTree/IndexedAvlTree.h"

// The AvlTreeDataStructure provides a concrete implementation of IDataStructure
// using your IndexedAvlTree. It also exposes begin() and end() that return the
// underlying tree's iterator by value so that structured bindings and range-based
// for loops work seamlessly.
template <typename id_type, typename data_type>
class AvlTreeDataStructure : public IDataStructure<id_type, data_type> {
private:
    Coil::IndexedAvlTree<id_type, data_type> tree;

public:
    virtual ~AvlTreeDataStructure() override = default;

    /* ============================================================================
     * --------------------------- Insert
     * Inserts a node into the AVL tree if it does not exist. If the node already
     * exists, returns a pointer to the stored data.
     *
     * ------ Parameters ------
     * id:    The key used for indexing.
     * data:  The data to insert if the key is not already present.
     *
     * ------ Returns --------
     * Pointer to the data stored in the node corresponding to 'id'.
     * ============================================================================
     */
    virtual data_type* Insert(const id_type& id, const data_type& data) override {
        return tree.Insert(id, data);
    }

    /* ============================================================================
     * --------------------------- Remove
     * Removes the node with the given key from the AVL tree.
     *
     * ------ Parameters ------
     * id:  The key identifying the node to remove.
     * ============================================================================
     */
    virtual void Remove(const id_type& id) override {
        tree.Remove(id);
    }

    /* ============================================================================
     * --------------------------- Find
     * Searches for the node with the given key and returns a pointer to its data.
     *
     * ------ Parameters ------
     * id:  The key to search for.
     *
     * ------ Returns --------
     * Pointer to the data if found; nullptr otherwise.
     * ============================================================================
     */
    virtual data_type* Find(const id_type& id) const override {
        return tree.Find(id);
    }

    /* ============================================================================
     * --------------------------- Clear
     * Clears the entire AVL tree.
     * ============================================================================
     */
    virtual void Clear() override {
        tree.Clear();
    }

    // Expose the underlying tree's iterator directly.
    auto begin() -> decltype(tree.begin()) {
        return tree.begin();
    }

    auto end() -> decltype(tree.end()) {
        return tree.end();
    }
};

#endif // AVL_DATASTRUCTURE_H
