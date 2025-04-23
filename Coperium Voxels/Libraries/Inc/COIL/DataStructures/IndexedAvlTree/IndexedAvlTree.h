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
            std::unique_ptr<node_t> children[2]{ nullptr };

            node_t(const id_type& id, const data_type& data) :
                id(id), data(data), height(1), children{ nullptr, nullptr } {}
        };

        typedef enum {
            L = 0,
            R = 1,
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
        data_type* Insert(const id_type& id, const data_type& data) {
            return Insert_Node(root, id, data);
        }

        /* ============================================================================
         * --------------------------- Remove
         * Remove a node given an item through the ID
         * ------ Parameters ------
         * id:      Indexable id by which to search and delete
         * ============================================================================
         */
        void Remove(const id_type& id) {
            Delete_Node(id, root);
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
            Insert_Node(root, id, data_type());
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
             * Default Constructor
             * ============================================================================
             */
            Iterator() {}

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
             * Dereferences the iterator to access the current node as a pair.
             * ------- Returns --------
             * A std::pair containing references to the node's id (first) and data (second)
             * ============================================================================
             */
            std::pair<id_type&, data_type&> operator*() {
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
        Iterator end() { return Iterator(); }

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
            return Get_Height(node->children[L].get()) - Get_Height(node->children[R].get());
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
            while (node->children[L]) { node = node->children[0].get(); }
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
                }
                else {
                    pivot = Rotate_LR(pivot);
                }

            }
            else if (balance < -1) {
                // --------------------------------- RIGHT LEFT
                if (Get_Balance(pivot->children[R].get()) > 0) {
                    pivot = Rotate_RL(pivot);
                }
                else {
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
        data_type* Insert_Node(std::unique_ptr<node_t>& node, const id_type& id, const data_type& data) {

            if (node == nullptr) {
                node = std::make_unique<node_t>(id, data);
                return &node->data;
            }
            else if (id == node->id) {
                return &node->data;
            }

            data_type* ret = Insert_Node(
                node->children[(id > node->id)],
                id, data
            );

            node->height = 1 + std::max(
                Get_Height(node->children[0].get()),
                Get_Height(node->children[1].get())
            );

            node = Balance(node);
            return ret;
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
        void Delete_Node(const id_type& id,
            std::unique_ptr<node_t>& node) {
            if (!node) return;

            if (node->id == id) {
                if (node->children[L] && node->children[R]) {
                    // 1) find the in-order successor
                    node_t* succ = Find_Min(node->children[R].get());

                    // 2) stash its key
                    id_type succ_id = succ->id;
                    data_type succ_dt = succ->data;

                    // 3) overwrite this node
                    node->id = succ_id;
                    node->data = succ_dt;

                    // 4) now delete the *original* successor
                    Delete_Node(succ_id, node->children[R]);
                }
                else if (node->children[L]) {
                    node = std::move(node->children[L]);
                }
                else if (node->children[R]) {
                    node = std::move(node->children[R]);
                }
                else {
                    node.reset();
                    return;
                }
            }
            else {
                Delete_Node(id,
                    (id < node->id
                        ? node->children[L]
                        : node->children[R]));
            }

            // re-compute height & rebalance
            node->height = 1 + std::max(
                Get_Height(node->children[L].get()),
                Get_Height(node->children[R].get()));
            node = Balance(node);
        }

        /* ============================================================================
         * --------------------------- Destroy_Tree
         * Recursive utility function to delete nodes in the tree
         * ------ Parameters ------
         * node:    Node from which to delete
         * ============================================================================
         */
        void Destroy_Tree(std::unique_ptr<node_t> node) {
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
            std::unique_ptr<node_t> pivot = std::move(node->children[L]);
            node->children[L] = std::move(pivot->children[R]);
            pivot->children[R] = std::move(node);

            // Correctly update heights:
            // Update the height of the old root (now pivot->children[R])
            pivot->children[R]->height =
                1 + std::max(
                    Get_Height(pivot->children[R]->children[0].get()),
                    Get_Height(pivot->children[R]->children[1].get())
                );
            // Update the height of the new root (pivot)
            pivot->height =
                1 + std::max(
                    Get_Height(pivot->children[0].get()),
                    Get_Height(pivot->children[1].get())
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
        std::unique_ptr<node_t> Rotate_L(std::unique_ptr<node_t>& node) {
            std::unique_ptr<node_t> pivot = std::move(node->children[R]);
            node->children[R] = std::move(pivot->children[L]);
            pivot->children[L] = std::move(node);

            // Correctly update heights:
            pivot->children[L]->height =
                1 + std::max(
                    Get_Height(pivot->children[L]->children[0].get()),
                    Get_Height(pivot->children[L]->children[1].get())
                );
            pivot->height =
                1 + std::max(
                    Get_Height(pivot->children[0].get()),
                    Get_Height(pivot->children[1].get())
                );
            return pivot;
        }
        /* ============================================================================
        * --------------------------- Rotate_LR
        * Left Right rotation of a subtree
        * ------ Parameters ------
        * node:    The node to rotate
        * ------- Returns --------
        * New root of the rotated subtree
        * ============================================================================
        */
        std::unique_ptr<node_t> Rotate_LR(std::unique_ptr<node_t>& node) {
            node->children[L] = Rotate_L(node->children[L]);
            return Rotate_R(node);
        }


        /* ============================================================================
        * --------------------------- Rotate_RL
        * Right Left rotation of a subtree
        * ------ Parameters ------
        * node:    The node to rotate
        * ------- Returns --------
        * New root of the rotated subtree
        * ============================================================================
        */
        std::unique_ptr<node_t> Rotate_RL(std::unique_ptr<node_t>& node) {
            node->children[R] = Rotate_R(node->children[R]);
            return Rotate_L(node);
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

            newNode->children[0] = Copy_Tree(node->children[0].get());
            newNode->children[1] = Copy_Tree(node->children[1].get());
            newNode->height = node->height;

            return newNode;
        }



    };

} // namespace Coil

#endif // !AVL_TREE_H
