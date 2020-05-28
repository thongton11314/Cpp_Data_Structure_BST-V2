#include <iostream>
#include <assert.h>
#include <fstream>
#include "bst.h"

using namespace std;

int main() {
    BSTree<int> tree;

    // Test insert
    assert(tree.insert(new int(20)));
    assert(tree.insert(new int(5)));
    assert(!tree.insert(new int(5)));
    assert(tree.insert(new int(35)));
    assert(tree.insert(new int(0)));
    assert(tree.insert(new int(15)));
    assert(tree.insert(new int(30)));
    assert(tree.insert(new int(45)));
    tree.display();
    cout << "Test insert: \tPASSED" << endl;

    // Test retrieve
    int target = 45;
    int* ptrTarget;
    assert(tree.retrieve(target, ptrTarget));
    *ptrTarget = 100; // modify to 100
    assert(tree.retrieve(*ptrTarget, ptrTarget));
    *ptrTarget = 45;  // modify back to 45
    assert(tree.retrieve(target, ptrTarget));
    target = 100;
    assert(!tree.retrieve(target, ptrTarget));
    cout << "Test retrieve: \tPASSED" << endl;

    // Test display
    tree.display();
    cout << "Test display: \tPASSED" << endl;

    // Test is empty
    assert(!tree.isEmpty());
    cout << "Test isEmpty: \tPASSED" << endl;

    // Test makeEmpty
    tree.makeEmpty();
    assert(tree.isEmpty());
    cout << "Test makeEmpty: PASSED" << endl;

    // After make the tree empty, add new node
    assert(tree.insert(new int(20)));
    assert(tree.insert(new int(5)));
    assert(tree.insert(new int(35)));
    assert(!tree.isEmpty());
    tree.display();

    // test deconstructor when end program

    return 0;
}