// Developer Thong Ton

#pragma once
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

// ADT Binary Search Tree
//
// Assumption:
//  - All keys in left subtree of a key must be smaller.
//  - All keys in right subtree must be greater.
//  - It has distinct keys and duplicates are not allowed.
//  - If the passed in node is already in tree, it will be deleted

// Implementation:
//  - Function insert, retrieve, display, makeEmpty will need sub-function to
//    help it traverse the tree recursively, 
//    insertHelper, retrieveHelper, displayHelper, emptyHelper will be called.

template <typename T>
class BSTree {
public:
    BSTree();  // constructor
    ~BSTree(); // deconstuctor, calls makeEmpty() which deallocates all memory

    // insert object into the tree, parameter holds pointer to object to insert
    bool insert(T *);

    // retrieve object, first parameter is object to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const T&, T*&) const;
    void display() const;            //displays the contents of a tree to cout
    void makeEmpty();                //empties the current tree, deallocates all memory
    bool isEmpty() const;            //returns true if tree is empty

private:

    struct Node {
        T* data;
        Node* right;
        Node* left;
    };
    Node* root;                      // root of the tree

    // use for traverse the tree to add node
    // first parameter is new node, second is for traversing
    bool insertHelper(T *, Node *&);

    // use for retrieve the node node
    // first parameter is target
    // second is for retriever
    // third parameter is for traversing
    bool retrieveHelper(const T &, T *&, Node*) const;

    // use for traverse the tree to delete node
    void makeEmptyHelper(Node *&);

    // use for treverse the tree to coud
    void displayHelper(Node *) const;

};

// constructor
// initialize the root
template<typename T>
BSTree<T>::BSTree() {
    root = nullptr;
}

// deconstructor
// delete every left and right subtree node
template<typename T>
BSTree<T>::~BSTree() {
    makeEmpty();
}

// insert
// insert new node to left or right subtree
// call the insertHelper to perform traverse recursively
// the passed in node will be taken and insert in tree
// if the node is already in tree, then the passed in node will be deleted
template<typename T>
bool BSTree<T>::insert(T * newNode) {

    // if tree is empty, this is the first node of tree
    if (root == nullptr) {

        // new node data for root. Left, right subtree are null pointer
        root = new Node{ newNode, nullptr, nullptr };
        return true;
    }
    
    // if tree is not empty
    else
        return insertHelper(newNode, root);
}

// insertHelper
// recursively traverse the tree
// this function is sub-function of insert
template<typename T>
bool BSTree<T>::insertHelper(T * newNode, Node *& current) {

    // base case
    if (current == nullptr) {
        current = new Node{ newNode, nullptr, nullptr };
        return true;
    }

    // travere left
    else if (*newNode < *current->data) {
        return insertHelper(newNode, current->left);
    }

    // traverse right
    else if (*newNode > *current->data) {
        return insertHelper(newNode, current->right);
    }

    // duplicate is not allow, it will be deleted
    else {
        delete newNode;
        return false;
    }
}

// retrieve
// retrieve the node that match with target
// call the retrieveHelper to perform traverse recursively
template<typename T>
bool BSTree<T>::retrieve(const T & target, T *& ptr) const {
    
    // return true if retrieve successfully, else return false
    return retrieveHelper(target, ptr, root);
}

// retrieveHelper
// recursively traverse the tree
// this function is sub-function of retrieve
template<typename T>
bool BSTree<T>::retrieveHelper(const T & target, T *& retriever, Node * current) const {

    // if not found target
    if (current == nullptr) {
        retriever = nullptr;
        return false;
    }

    // travere left
    if (target < *current->data) {
        return retrieveHelper(target, retriever, current->left);
    }

    // traverse right
    else if (target > *current->data) {
        return retrieveHelper(target, retriever, current->right);
    }

    // if found target
    else {
        retriever = current->data;
        return true;
    }
}

// display
// display the node of tree from left to right, by acessding order
// call the displayHelper to perform traverse recursively
template<typename T>
void BSTree<T>::display() const {
    
    // display the tree from left to right
    displayHelper(root);
}

// displayHelper
// recursively traverse the tree
// this function is sub-function of display
template<typename T>
void BSTree<T>::displayHelper(Node * current) const {

    // base case
    if (current == nullptr)
        return;

    // recursive print in increasing order
    else {
        displayHelper(current->left);
        std::cout << *current->data << std::endl;
        displayHelper(current->right);
    }
}

// makeEmpty
// delete every node from the tree
// this function will be called when deconstructor is called
template<typename T>
void BSTree<T>::makeEmpty() {
    
    // early exit if root is null pointer
    if (root == nullptr)
        return;

    // delete every node
    makeEmptyHelper(root);

    // always make root become null pointer
    root = nullptr;
}

// makeEmptyHelper
// recursively traverse the tree
// this function is sub-function of makeEmpty
template<typename T>
void BSTree<T>::makeEmptyHelper(Node *& current) {

    // delete every node
    if (current != nullptr) {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);
        delete current->data;   // delete node data
        delete current;         // delete node
   }
}

// isEmpty
// check if the tree has any node or not
template<typename T>
bool BSTree<T>::isEmpty() const {
    return root == nullptr;
}

#endif // !BINARY_SEARCH_TREE