#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <stack>

namespace Coil {

template <typename id_type, typename data_type>
class IndexedAvlTree {
private:
    // --------------------------------- Node Struct
    struct node_t {
        id_type id;
        data_type data;
        int height;
        std::unique_ptr<node_t> children[2]{nullptr};

        node_t(const id_type& id, const data_type& data) : 
            id(id), data(data), height(1), children{nullptr, nullptr} {}
    };

    typedef enum {
        L  = 0,
        R  = 1,
    }dir_t;

public:
    /* ============================================================================
     * --------------------------- IndexedAvlTree
     * Default constructor that sets the tree as null
     * ============================================================================
     */
    IndexedAvlTree() : root(nullptr) {}

    /* ============================================================================
     * --------------------------- ~IndexedAvlTree
     * Destructor that makes sure to destroy the tree.
     * ============================================================================
     */
    ~IndexedAvlTree() {
        Destroy_Tree(std::move(root));
    }

    /* ============================================================================
     * --------------------------- Insert
     * Inserts a node into the AVL tree.
     * ------ Parameters ------
     * id:      Indexable id by which to search and access
     * data:    Data being added to the tree
     * ============================================================================
     */
    void Insert(const id_type& id, const data_type& data) {
        root = Insert_Node(std::move(root), id, data);
    }

    /* ============================================================================
     * --------------------------- Remove
     * Remove a node given an item through the ID
     * ------ Parameters ------
     * id:      Indexable id by which to search and delete
     * ============================================================================
     */
    void Remove(const id_type& id) {
        root = Delete_Node(std::move(root), id);
    }

    /* ============================================================================
     * --------------------------- Find
     * Finds and returns the data type indexed by the id field
     * ------ Parameters ------
     * id:      Indexable id by which to search and return
     * ============================================================================
     */
    data_type* Find(const id_type& id) const {
        node_t* result = Search_Node(id);
        return result == nullptr ? nullptr : &result->data;
    }

    /* ============================================================================
     * --------------------------- Create_Node
     * Creates a node at a specified location.
     * ------ Parameters ------
     * id:      Indexable id by which to search and access
     * ============================================================================
     */
    void Create_Node(const id_type& id) {
        root = Insert_Node(std::move(root), id, data_type());
    }

    /* ============================================================================
     * --------------------------- Clear
     * Clears the entire tree
     * ============================================================================
     */
    void Clear() {
        Destroy_Tree(std::move(root));
        root = nullptr;
    }

    /* ============================================================================
     * --------------------------- operator=
     * Overrides the = operator to perform a deep copy
     * ============================================================================
     */
    IndexedAvlTree& operator=(const IndexedAvlTree& other) {
        if (this != &other) {

            Clear();

            if (other.root) { 
                root = Copy_Tree(other.root.get());
            }
        }
        return *this;
    }

    // --------------------------------- ITERATOR
    class Iterator {
    public:
        /* ============================================================================
         * --------------------------- Iterator
         * Constructor that initializes the iterator to the leftmost node (smallest id)
         * ------ Parameters ------
         * root:    Root node of the AVL tree from which the iteration will start
         * ============================================================================
         */
        Iterator(node_t* root) {
            while (root) {
                nodeStack.push(root);
                root = root->children[L].get();
            }
        }

        /* ============================================================================
         * --------------------------- operator*
         * Dereferences the iterator to access the data of the current node
         * ------- Returns --------
         * Reference to the data stored in the current node
         * ============================================================================
         */
        std::pair<const id_type&, data_type&> operator*() {
            node_t* node = nodeStack.top();
            return { node->id, node->data };
        }

        /* ============================================================================
         * --------------------------- operator++
         * Advances the iterator to the next node in in-order traversal
         * ------- Returns --------
         * Reference to the iterator after it has been incremented
         * ============================================================================
         */
        Iterator& operator++() {
            if (nodeStack.empty()) return *this;

            node_t* node = nodeStack.top();
            nodeStack.pop();

            if (node->children[R]) {
                node = node->children[R].get();
                while (node) {
                    nodeStack.push(node);
                    node = node->children[L].get();
                }
            }

            return *this;
        }

        /* ============================================================================
         * --------------------------- operator!=
         * Compares two iterators for inequality
         * ------ Parameters ------
         * other:   Another iterator to compare with
         * ------- Returns --------
         * True if the iterators are not equal; false otherwise
         * ============================================================================
         */
        bool operator!=(const Iterator& other) const {
            return nodeStack != other.nodeStack; // Compare the stacks for inequality
        }

    private:
        std::stack<node_t*> nodeStack;
    };

    Iterator begin() { return Iterator(root.get()); }
    Iterator end()   { return Iterator()          ; }

private:
    // --------------------------------- VARIABLES
    std::unique_ptr<node_t> root;

    // --------------------------------- HELPER FUNCTIONS
    /* ============================================================================
     * --------------------------- Get_Height
     * Safely gets the height of a given node
     * ------ Parameters ------
     * node:    Node on which the height is calculated
     * ------- Returns --------
     * Height of the node
     * ============================================================================
     */
    int Get_Height(node_t* node) {
        if (node != nullptr) { return node->height; }
        return 0;
    }

    /* ============================================================================
     * --------------------------- Get_Balance
     * Safely gets the Balance of a given node
     * ------ Parameters ------
     * node:    Node on which the balance is calculated
     * ------- Returns --------
     * Balance of the node
     * ============================================================================
     */
    int Get_Balance(node_t* node) {
        if (node == nullptr) { return 0; }
        return Get_Height(node->children[0].get()) - Get_Height(node->children[1].get());
    }

    /* ============================================================================
     * --------------------------- Find_Min
     * Finds the leftmost node from a given SubRoot/Root
     * ------ Parameters ------
     * node:    Node from which to search the smallest root
     * ------- Returns --------
     * The smallest/leftmost node
     * ============================================================================
     */
    node_t* Find_Min(node_t* node) {
        while (node->children[0]) node = node->children[0].get();
        return node;
    }

    /* ============================================================================
     * --------------------------- Search_Node
     * Searches for a node using a given id and returns the node.
     * ------ Parameters ------
     * id:      Indexable id by which to search
     * ============================================================================
     */
    node_t* Search_Node(const id_type& id) const {
        node_t* node = root.get();
        while (node != nullptr) {
            if (id == node->id) return node;
            node = node->children[id > node->id].get();
        }
        return nullptr;
    }

    /* ============================================================================
     * --------------------------- Balance
     * Makes sure that the tree is balanced at a given node.
     * ------ Parameters ------
     * pivot:       Node at which to check
     * ============================================================================
     */
    std::unique_ptr<node_t> Balance(std::unique_ptr<node_t>& pivot) {

        int balance = Get_Balance(pivot.get());

        if (balance > 1) {
            // --------------------------------- LEFT LEFT
            if (Get_Balance(pivot->children[L].get()) > 0) {
                pivot = Rotate_R(pivot);
            // --------------------------------- LEFT RIGHT
            } else {
                pivot = Rotate_LR(pivot);
            }

        }else if (balance < -1) {
            // --------------------------------- RIGHT LEFT
            if (Get_Balance(pivot->children[R].get()) > 0) {
                pivot = Rotate_RL(pivot);
            } else {
                pivot = Rotate_L(pivot);
            }
        }
        return std::move(pivot);
    }


    /* ============================================================================
     * --------------------------- Insert_Node
     * Utility Function that inserts a node through a recursive process while
     * also making sure that the tree is balanced by the end of it.
     * ------ Parameters ------
     * node:    Node at which the current recursive step is at
     * id:      Indexable id by which to index by and the new key for the data
     * data:    Data item to be inserted
     * ------- Returns --------
     * The new subhead node
     * ============================================================================
     */
    std::unique_ptr<node_t> Insert_Node(std::unique_ptr<node_t> node, const id_type& id, const data_type& data) {
        if (node == nullptr) {
            return std::make_unique<node_t>(id, data);
        } else if (id == node->id) {
            return node;
        }

        int direction = (id > node->id);
        node->children[direction] = Insert_Node(std::move(node->children[direction]), id, data);

        node->height = 1 + std::max(
            Get_Height(node->children[0].get()),
            Get_Height(node->children[1].get())
        );

        int balance = Get_Balance(node.get());

        // --------------------------------- Left Left rotate
        if (balance > 1 && id < node->children[0]->id) {
            return Rotate_R(std::move(node));
        }
        // --------------------------------- Right Right Case 
        else if (balance < -1 && id > node->children[1]->id) {
            return Rotate_L(std::move(node));
        }
        // --------------------------------- Left Right Case
        else if (balance > 1 && id > node->children[0]->id) {
            node->children[0] = Rotate_L(std::move(node->children[0]));
            return Rotate_R(std::move(node));
        }
        // --------------------------------- Right Left Case  
        else if (balance < -1 && id < node->children[1]->id) {
            node->children[1] = Rotate_R(std::move(node->children[1]));
            return Rotate_L(std::move(node));
        }

        return node;
    }

    /* ============================================================================
     * --------------------------- Delete_Node
     * Utility Function that deletes a node through a recursive process while
     * also making sure that the tree is balanced by the end of it.
     * ------ Parameters ------
     * node:    Node at which the current recursive step is at
     * id:      Indexable id by which to index by and the key for the data
     * ------- Returns --------
     * The new subhead node
     * ============================================================================
     */
    std::unique_ptr<node_t> Delete_Node(std::unique_ptr<node_t> node, const id_type& id) {
        if (!node) return nullptr;

        int direction = (id > node->id);

        if (id < node->id) {
            node->children[0] = Delete_Node(std::move(node->children[0]), id);
        } else if (id > node->id) {
            node->children[1] = Delete_Node(std::move(node->children[1]), id);
        } else {
            if (!node->children[0]) return std::move(node->children[1]);
            else if (!node->children[1]) return std::move(node->children[0]);
            node_t* temp = Find_Min(node->children[1].get());
            node->id = temp->id;
            node->data = temp->data;
            node->children[1] = Delete_Node(std::move(node->children[1]), temp->id);
        }

        // Update the height of the current node
        node->height = 
            1 + std::max(
                Get_Height(node->children[0].get()), 
                Get_Height(node->children[1].get())
            );
        int balance = Get_Balance(node.get());

        // Balance the tree
        // --------------------------------- Left Left rotate
        if (balance > 1 && Get_Balance(node->children[0].get()) >= 0) {
            return Rotate_R(std::move(node));
        }
        // --------------------------------- Right Right Case 
        else if (balance < -1 && Get_Balance(node->children[1].get()) <= 0) {
            return Rotate_L(std::move(node));
        }
        // --------------------------------- Left Right Case
        else if (balance > 1 && Get_Balance(node->children[0].get()) < 0) {
            node->children[0] = Rotate_L(std::move(node->children[0]));
            return Rotate_R(std::move(node));
        }
        // --------------------------------- Right Left Case  
        else if (balance < -1 && Get_Balance(node->children[1].get()) > 0) {
            node->children[1] = Rotate_R(std::move(node->children[1]));
            return Rotate_L(std::move(node));
        }

        return node;
    }

    /* ============================================================================
     * --------------------------- Destroy_Tree
     * Recursive utility function to delete nodes in the tree
     * ------ Parameters ------
     * node:    Node from which to delete
     * ============================================================================
     */
    void Destroy_Tree(std::unique_ptr<node_t>& node) {
        if (!node) return;
        Destroy_Tree(std::move(node->children[0]));
        Destroy_Tree(std::move(node->children[1]));
    }

    /* ============================================================================
     * --------------------------- Rotate_R
     * Right rotation of a subtree
     * ------ Parameters ------
     * node:    The node to rotate
     * ------- Returns --------
     * New root of the rotated subtree
     * ============================================================================
     */
    std::unique_ptr<node_t> Rotate_R(std::unique_ptr<node_t>& node) {

        std::unique_ptr<node_t> pivot = std::move(node.children[L]);
        node.children[L]    = std::move(pivot.children[L]);
        pivot.children[R]   = std::move(node);

        pivot.children[R]->height = 
            1 + std::max(
                Get_Height(pivot->children[L]->children[L].get()),
                Get_Height(pivot->children[L]->children[R].get())
            );
        pivot->height =
            1 + std::max(
                Get_Height(pivot->children[L].get()),
                Get_Height(pivot->children[L].get())
            );
        return pivot;
    }

    /* ============================================================================
     * --------------------------- Rotate_L
     * Left rotation of a subtree
     * ------ Parameters ------
     * node:    The node to rotate
     * ------- Returns --------
     * New root of the rotated subtree
     * ============================================================================
     */
    std::unique_ptr<node_t> Rotate_L(std::unique_ptr<node_t> node) {
        // Check if the left child is nullptr
        if (!node || !node->children[0]) {
            return std::move(node);
        }

        std::unique_ptr<node_t> newRoot = std::move(node->children[0]);
        node->children[0] = std::move(newRoot->children[1]);
        newRoot->children[1] = std::move(node);

        // Update heights after rotation
        node->height =
            1 + std::max(
                Get_Height(node->children[0].get()),
                Get_Height(node->children[1].get())
            );

        newRoot->height =
            1 + std::max(
                Get_Height(newRoot->children[0].get()),
                Get_Height(newRoot->children[1].get())
            );

        return newRoot;
    }
    /* ============================================================================
     * --------------------------- Copy_Tree
     * Copies the Nodes of a Subtree
     * ------ Parameters ------
     * node:    The node to Copy
     * ------- Returns --------
     * New root of the Copied Tree
     * ============================================================================
     */
    std::unique_ptr<node_t> Copy_Tree(const node_t* node) {
        if (!node) return nullptr;

        auto newNode = std::make_unique<node_t>(node->id, node->data);

        newNode->children[0]    = Copy_Tree(node->children[0].get());
        newNode->children[1]    = Copy_Tree(node->children[1].get());
        newNode->height         =           node->height;

        return newNode;
    }



};

} // namespace Coil

#endif // !AVL_TREE_H
