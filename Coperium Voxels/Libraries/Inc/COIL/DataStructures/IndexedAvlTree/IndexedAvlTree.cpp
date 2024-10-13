#include "IndexedAvlTree.h"

namespace Coil{
/* ============================================================================
 * --------------------------- IndexedAvlTree
 * Defualt constructor that sets the tree as null
 * ============================================================================
 */
template <typename id_type, typename data_type>
IndexedAvlTree<id_type, data_type>::IndexedAvlTree() : root(nullptr){}

/* ============================================================================
 * --------------------------- ~IndexedAvlTree
 * Deconstructor that makes sure to destroy the tree.
 * ============================================================================
 */
template <typename id_type, typename data_type>
IndexedAvlTree<id_type, data_type>::~IndexedAvlTree(){
    Destroy_Tree(root);
}

/* ============================================================================
 * --------------------------- Insert
 * Deconstructor that makes sure to destroy the tree.
 * 
 * ------ Parameters ------
 * id:      Indexible id by which to search and access
 * data:    Data being added to the tree
 * ============================================================================
 */
template <typename id_type, typename data_type>
void IndexedAvlTree<id_type, data_type>::Insert(
    const id_type& id, const data_type& data
){
    root = Insert_Node(std::move(root), id, data);
}

/* ============================================================================
 * --------------------------- Remove
 * Remove a node given an item through the ID
 * ------ Parameters ------
 * id:      Indexible id by which to search and delete
 * ============================================================================
 */
template <typename id_type, typename data_type>
void IndexedAvlTree<id_type, data_type>::Remove(
    const id_type& id
){
    root = Delete_Node(std::move(root), id);
}

/* ============================================================================
 * --------------------------- Find
 * Finds and returns the data type indexed by the id field
 * ------ Parameters ------
 * id:      Indexible id by which to search and return
 * ============================================================================
 */
template <typename id_type, typename data_type>
data_type* IndexedAvlTree<id_type, data_type>::Find(
    const id_type& id
)const{

    node_t* result = Search_Node(id);

    if(result == nullptr){return nullptr;}
    
    return &result->data;
}

/* ============================================================================
 * --------------------------- Create_Node
 * Creates a node at a specified location.
 * ------ Parameters ------
 * id:      Indexible id by which to search and access
 * ============================================================================
 */
template <typename id_type, typename data_type>
void IndexedAvlTree<id_type, data_type>::Create_Node(
    const id_type& id
){
    root = Insert_Node(std::move(root), id, data_type());
}

/* ============================================================================
 * --------------------------- Clear
 * Clears the Entire Tree
 * ============================================================================
 */
template <typename id_type, typename data_type>
void IndexedAvlTree<id_type, data_type>::Clear(){
    Destroy_Tree(std::move(root));
    root = nullptr;
}

/* ============================================================================
 * --------------------------- Search_Node
 * Searches for a node using a given id and returns the node.
 * ------ Parameters ------
 * id:      Indexible id by which to search
 * ============================================================================
 */
template <typename id_type, typename data_type>
typename IndexedAvlTree<id_type, data_type>::node_t* 
IndexedAvlTree<id_type, data_type>::Search_Node(
    const id_type& id
) const {

    node_t* node = root.get();

    while (node != nullptr){
        if (id == node->id){ return node; }

        node = node->children[id > node->id].get();
    }
    return nullptr;
}

/* ============================================================================
 * --------------------------- Insert_Node
 * Utility Function that inserts a node through a recursive process while
 * also making sure that the tree is balanced by the end of it.
 * ------ Parameters ------
 * node:    Node at which the current recursive step is at
 * id:      Indexible id by which to index by and the new key for the data
 * data:    data item to be inserted
 * ------- Returns --------
 * The new subhead node
 * ============================================================================
 */
template <typename id_type, typename data_type>
std::unique_ptr<typename IndexedAvlTree<id_type, data_type>::node_t> 
IndexedAvlTree<id_type, data_type>::Insert_Node(
    std::unique_ptr<node_t> node, const id_type& id, const data_type& data
){
    if (!node){
        return std::make_unique<node_t>(id, data);
    }else if (id == node->id){
        return node;
    }


    int direction = (id > node->id);
    node->children[direction] = 
        Insert_Node(std::move(node->children[direction]), id, data);


    node->height = 
        1 + std::max(
            Get_Height(node->children[0].get()), 
            Get_Height(node->children[1].get())
        );


    int balance = Get_Balance(node.get());

    // --------------------------------- Left Left rotate
    if          (balance >  1 && id < node->children[0]->id){
        return Rotate_R(std::move(node));

    // -------------------------------- Right Right Case 
    } else if   (balance < -1 && id > node->children[1]->id){
        return Rotate_L(std::move(node));

    // -------------------------------- Left Right Case
    } else if   (balance >  1 && id > node->children[0]->id){
        node->children[0] = 
            Rotate_L(std::move(node->children[0]));
        return Rotate_R(std::move(node));

    // -------------------------------- Right Left Case  
    } else if   (balance < -1 && id < node->children[1]->id){
        node->children[1] = 
            Rotate_R(std::move(node->children[1]));
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
 * id:      Indexible id by which to index by and delete by
 * ------- Returns --------
 * The new subhead node
 * ============================================================================
 */
template <typename id_type, typename data_type>
std::unique_ptr<typename IndexedAvlTree<id_type, data_type>::node_t> 
IndexedAvlTree<id_type, data_type>::Delete_Node(
    std::unique_ptr<node_t> node, const id_type& id
){
    
    if (!node){ return node; };

    if (id  ==  node->id){
        if (!node->children[0] || !node->children[1]){
                return std::move(
                    node->children[0] ? node->children[0] : node->children[1]);
            } else {
                node_t* minNode = Find_Min(node->children[1].get());
                node->id = minNode->id;
                node->data = minNode->data;
                node->children[1] = 
                    Delete_Node(std::move(node->children[1]), minNode->id);
            }
    }else{
        node->children[id > node->id] = 
            Delete_Node(std::move(id > node->id), id);
    }

    node->height = 
        1 + std::max(
            Get_Height(node->children[0].get()), 
            Get_Height(node->children[1].get())
        );

    int balance = Get_Balance(node.get());

    // --------------------------------- Left Left rotate
    if          (balance >  1 && Get_Balance(node->children[0].get()) >= 0){
        return Rotate_R(std::move(node));

    // -------------------------------- Right Right Case 
    }else if    (balance < -1 && Get_Balance(node->children[1].get()) <= 0){
        return Rotate_L(std::move(node));

    // -------------------------------- Left Right Case
    }else if    (balance >  1 && Get_Balance(node->children[0].get()) <  0){
        node->children[0] = Rotate_L(std::move(node->children[0]));
        return Rotate_R(std::move(node));

    // -------------------------------- Right Left Case  
    }else if    (balance < -1 && Get_Balance(node->children[1].get()) >  0){
        node->children[1] = Rotate_R(std::move(node->children[1]));
        return Rotate_L(std::move(node));
    }

    return node;
}

/* ============================================================================
 * --------------------------- Find_Min
 * Finds the left most node from a given SubRoot/Root
 * ------ Parameters ------
 * node:    Node from which to search the smalest root
 * ------- Returns --------
 * The smallest/leftmost node
 * ============================================================================
 */
template <typename id_type, typename data_type>
typename IndexedAvlTree<id_type, data_type>::node_t* 
IndexedAvlTree<id_type, data_type>::Find_Min(
    node_t* node
){
    while (node->children[0]) node = node->children[0].get();
    return node;

}

/* ============================================================================
 * --------------------------- Rotate_R
 * Performs a Right Rotation
 * ------ Parameters ------
 * y:       Node on which to rotate
 * ------- Returns --------
 * New Head Node
 * ============================================================================
 */
template <typename id_type, typename data_type>
std::unique_ptr<typename IndexedAvlTree<id_type, data_type>::node_t> 
IndexedAvlTree<id_type, data_type>::Rotate_R(
    std::unique_ptr<node_t> y
){
    
    std::unique_ptr<node_t> x = std::move(y->children[0]);

    y->children[0] = std::move(x->children[1]);
    x->children[1] = std::move(y);
    
    x->children[1]->height = 
        1 + std::max(
            Get_Height(x->children[1]->children[0].get()), 
            Get_Height(x->children[1]->children[1].get())
        );

    x->height = 
        1 + std::max(
            Get_Height(x->children[0].get()), 
            Get_Height(x->children[1].get())
        );

    return x;
}

/* ============================================================================
 * --------------------------- Rotate_L
 * Performs a Left Rotation
 * ------ Parameters ------
 * y:       Node on which to rotate
 * ------- Returns --------
 * New Head Node
 * ============================================================================
 */
template <typename id_type, typename data_type>
std::unique_ptr<typename IndexedAvlTree<id_type, data_type>::node_t> 
IndexedAvlTree<id_type, data_type>::Rotate_L(
    std::unique_ptr<node_t> x
){
    
    std::unique_ptr<node_t> y = std::move(x->children[1]);

    x->children[1] = std::move(y->children[0]);
    y->children[0] = std::move(x);

    y->children[0]->height = 
        1 + std::max(
            Get_Height(y->children[0]->children[0].get()), 
            Get_Height(y->children[0]->children[1].get())
        );
    y->height = 
        1 + std::max(
            Get_Height(y->children[0].get()), 
            Get_Height(y->children[1].get())
        );

    return y;
}

/* ============================================================================
 * --------------------------- Get_Height
 * Safely gets the height of a given node
 * ------ Parameters ------
 * node:    Node on which the height is calculated
 * ------- Returns --------
 * Height of the node
 * ============================================================================
 */
template <typename id_type, typename data_type>
int IndexedAvlTree<id_type, data_type>::Get_Height(node_t* node){
    return node ? node->height : 0;
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
template <typename id_type, typename data_type>
int IndexedAvlTree<id_type, data_type>::Get_Balance(node_t* node){
    return 
        node ? 
            Get_Height(node->children[0].get()) - 
            Get_Height(node->children[1].get()) 
        : 0;
}

/* ============================================================================
 * --------------------------- Destroy_Tree
 * Deletes the entire tree
 * ------ Parameters ------
 * node:    Node on which the deletion will start
 * ============================================================================
 */
template <typename id_type, typename data_type>
void IndexedAvlTree<id_type, data_type>::Destroy_Tree(
    std::unique_ptr<node_t>& node
){
    node.reset();
}

/* ============================================================================
 * --------------------------- Iterator
 * Constructor that initializes the iterator to the leftmost node (smallest id)
 * ------ Parameters ------
 * root:    Root node of the AVL tree from which the iteration will start
 * ============================================================================
 */
template <typename id_type, typename data_type>
IndexedAvlTree<id_type, data_type>::Iterator::Iterator(node_t* root) {
    while (root) {
        nodeStack.push(root);
        root = root->children[0].get();
    }
}

/* ============================================================================
 * --------------------------- operator*
 * Dereferences the iterator to access the data of the current node
 * ------- Returns --------
 * Reference to the data stored in the current node
 * ============================================================================
 */
template <typename id_type, typename data_type>
data_type& IndexedAvlTree<id_type, data_type>::Iterator::operator*() {
    return nodeStack.top()->data; // Return the data at the top node
}

/* ============================================================================
 * --------------------------- operator++
 * Advances the iterator to the next node in in-order traversal
 * ------- Returns --------
 * Reference to the iterator after it has been incremented
 * ============================================================================
 */
template <typename id_type, typename data_type>
typename IndexedAvlTree<id_type, data_type>::Iterator&
IndexedAvlTree<id_type, data_type>::Iterator::operator++() {
    if (nodeStack.empty()) return *this; // Do nothing if stack is empty

    node_t* node = nodeStack.top();
    nodeStack.pop(); // Remove the node from the stack

    // Push the right child and its left descendants onto the stack
    if (node->children[1]) {
        node = node->children[1].get();
        while (node) {
            nodeStack.push(node);
            node = node->children[0].get();
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
template <typename id_type, typename data_type>
bool IndexedAvlTree<id_type, data_type>::Iterator::operator!=(const Iterator& other) const {
    return nodeStack != other.nodeStack; // Compare the stacks for inequality
}


} // Coil