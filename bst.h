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
    BSTree();                   // constructor
    BSTree(const BSTree<T> &);  // copy constructor
    ~BSTree(); // deconstuctor, calls makeEmpty() which deallocates all memory

    // insert object into the tree, parameter holds pointer to object to insert
    bool insert(T *);

    // retrieve object, first parameter is object to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const T&, T*&) const;
    int count();                // count total node
    int countUp(int);           // count the node up level
    int countDown(int);         // count the node down level
    int maxDepth();             // max depth of the tree
    T getMin() const;           // get min value
    T getMax() const;           // get max value
    bool isSameTree(BSTree<T>); // check if other tree is identical this tree
    void display() const;       // displays the contents of a tree to cout
    void makeEmpty();           // empties the current tree, deallocates all memory
    bool isEmpty() const;       // returns true if tree is empty

private:

    struct Node {
        T* data;
        Node* right;
        Node* left;
    };
    Node* root;                     // root of the tree

    void copy(Node *&, Node*);       // use to copy other tree

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

    // count total number of node
    int countHelper(Node*);

    // use for count up
    // first parameter is node
    // second parameter is level
    // third parameter is n
    int countUpHelper(Node *, int, int);

    // use for count down
    // first parameter is node
    // second parameter is level
    int countDownHelper(Node *, int);

    // get the longest length of tree
    int maxDeepHelper(Node *);

    // get minimum value of tree
    T getMinHelper(Node*) const;

    // get maximum value of tree
    T getMaxHelper(Node*) const;

    // check if two tree are identical
    bool sameTreeHelper(Node*, Node*) const;
};

// constructor
// initialize the root
template<typename T>
BSTree<T>::BSTree() {
    root = nullptr;
}

// copy constructor
// copy other tree into this tree
template<typename T>
BSTree<T>::BSTree(const BSTree<T> &other) {

    // early exit
    if (other.root == nullptr)
        root = nullptr;
    else
        copy(root, other.root);
}

// copy
// recursively traverse the other tree
// this function will be call in copy constructor
template<typename T>
void BSTree<T>::copy(Node *& current, Node * other) {
    if (other == nullptr)
        return;
    else {
        current = new Node{ new T(*other->data), nullptr, nullptr };
        copy(current->left, other->left);
        copy(current->right, other->right);
    }
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

// count
// count total number of node in tree
template<typename T>
int BSTree<T>::count() {
    return countHelper(root);
}

// countHelper
// recursively traverse the tree
template<typename T>
int BSTree<T>::countHelper(Node * current) {
    if (current == nullptr)
        return 0;
    return countHelper(current->left)
         + countHelper(current->right)
         + 1;
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

// countUp
// count how many node at level n
// root is level 0
template<typename T>
int BSTree<T>::countUp(int n) {
    int level = 0;
    return countUpHelper(root, level, n);
}

// countUpHelper
// recursively count up
// this function is sub-function of count up
template<typename T>
int BSTree<T>::countUpHelper(Node * current, int level, int n) {
    if (current == NULL)
        return 0;
    if (level == n)
        return 1;
    level++;
    return countUpHelper(current->left, level, n)
         + countUpHelper(current->right, level, n);
    return 0;
}

// countDown
// count how many node at level n
// root is level 0
template<typename T>
int BSTree<T>::countDown(int n) {
    return countDownHelper(root, n);
}

// countDownHelper
// recursively count up
// this function is sub-function of count down
template<typename T>
int BSTree<T>::countDownHelper(Node * current, int n) {
    if (current == NULL)
        return 0;
    if (n == 0)
        return 1;
    return countDownHelper(current->left, n - 1)
         + countDownHelper(current->right, n - 1);
}

// maxDepth
// the longest path from the root node down to the farthest leaf node
// at root is level 0
template<typename T>
int BSTree<T>::maxDepth() {

    if (root == nullptr)
        return 0;
    else
        return maxDeepHelper(root) - 1; // count from 0
}

// maxDeepHelper
// recursively traverse the tree
// this function will be called in maxDepth
template<typename T>
int BSTree<T>::maxDeepHelper(Node * current) {
    
    // base case
    if (current == nullptr) {
        return 0;
    }

    // traversing
    else {

        // compute the depth of each subtree
        int lDepth = maxDeepHelper(current->left);
        int rDepth = maxDeepHelper(current->right);

        // use the larger one
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}   

// getMin
// return minimum value of tree
template<typename T>
T BSTree<T>::getMin() const {
    if (root == nullptr)
        return *root->data;
    return getMinHelper(root);
}

// getMinHelper
// recursively traverse the left-sub tree
// this function will be called in getMin
template<typename T>
T BSTree<T>::getMinHelper(Node * current) const {
    if (current->left == nullptr)
        return *current->data;
    else
        return getMinHelper(current->left);
}

// getMax
// return maximum value of tree
template<typename T>
T BSTree<T>::getMax() const {
    if (root == nullptr)
        return *root->data;
    return getMaxHelper(root);
}

// getMaxHelper
// recursively traverse the right-sub tree
// this function will be called in getMax
template<typename T>
T BSTree<T>::getMaxHelper(Node * current) const {
    if (current->left == nullptr)
        return *current->data;
    else
        return getMaxHelper(current->right);
}

// sameTree
// two identical tree mush have same structure and value
template<typename T>
bool BSTree<T>::isSameTree(BSTree<T> other) {

    // early exit if not
    if (root != other.root)
        return false;
    else
        return sameTreeHelper(root, other.root);
}

// sameTreeHelper
// recursively compare each left-sub, right-sub tree
// this function will be called in sameTree
template<typename T>
bool BSTree<T>::sameTreeHelper(Node * thisTree, Node * otherTree) const {
    if (thisTree == nullptr && otherTree == nullptr)
        return true;
    if (thisTree == nullptr || otherTree == nullptr)
        return false;
    else
        return thisTree == otherTree
        && sameTreeHelper(thisTree->left, otherTree->left)
        && sameTreeHelper(thisTree->right, otherTree->right);
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