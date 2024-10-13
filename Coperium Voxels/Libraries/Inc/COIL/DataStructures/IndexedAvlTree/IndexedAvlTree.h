#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <stack>

namespace Coil{

template <typename id_type, typename data_type>
class IndexedAvlTree {
private:
    // --------------------------------- Node Struct
    struct node_t{
        id_type     id;
        data_type   data;
        int         height;
        std::unique_ptr<node_t> children[2];

        node_t(const id_type& id, const data_type& data): 
            id      (id)    , data      (data),
            height  (1)     , children  {nullptr, nullptr}
        {}
    };
public:
     IndexedAvlTree();
    ~IndexedAvlTree();

    // --------------------------------- INTERFACE
    data_type*  Find        (const id_type&     id  ) const;
    void        Insert      (const id_type&     id, 
                             const data_type&   data);
    void        Remove      (const id_type&     id  );
    void        Create_Node (const id_type&     id  );
    void        Clear       ();


    // --------------------------------- ITERATOR
    class Iterator {
    public:
        Iterator() = default;
        Iterator(node_t* root);
        
        data_type&  operator*   ();
        Iterator&   operator++  ();
        bool        operator!=  (const Iterator& other) const;

    private:
        std::stack<node_t*> nodeStack;
    };

    Iterator begin()    { return Iterator(root.get()); }
    Iterator end()      { return Iterator(          ); }



private:
    
    // --------------------------------- VARIABLES
    std::unique_ptr<node_t> root;

    // --------------------------------- HELPER FUNCTIONS
    int                     Get_Height  (node_t*                    node    );
    int                     Get_Balance (node_t*                    node    );
    node_t*                 Find_Min    (node_t*                    node    );
    node_t*                 Search_Node (const id_type&             id      )const;
    std::unique_ptr<node_t> Insert_Node (std::unique_ptr<node_t>    node, 
                                         const id_type&             id, 
                                         const data_type&           data    );
    std::unique_ptr<node_t> Delete_Node (std::unique_ptr<node_t>    node, 
                                         const id_type&             id      );
    std::unique_ptr<node_t> Rotate_R    (std::unique_ptr<node_t>    y       );
    std::unique_ptr<node_t> Rotate_L    (std::unique_ptr<node_t>    x       );
    void                    Destroy_Tree(std::unique_ptr<node_t>&   node);
};
}

#include "IndexedAvlTree.cpp"

#endif
