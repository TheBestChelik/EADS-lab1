#include "avl_tree.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_insert_find()
{
    avl_tree<int, std::string> tree;

    // Test 1: Inserting elements into the tree
    tree.insert(10, "Apple");
    assert(tree.isBalanced());
    tree.insert(5, "Banana");
    assert(tree.isBalanced());
    tree.insert(15, "Cherry");
    assert(tree.isBalanced());

    // Verify that the elements are correctly inserted
    assert(tree.find(10)); // Check if 10 exists in the tree
    assert(tree.find(5));  // Check if 5 exists in the tree
    assert(tree.find(15)); // Check if 15 exists in the tree

    assert(tree.find(11) == false); // Check not existing element

    cout << "All tests insert and find tests passed" << endl;
}

void test_insert_get()
{
    avl_tree<int, std::string> tree;

    // Test 1: Inserting elements into the tree
    tree.insert(10, "Apple");
    tree.insert(5, "Banana");
    tree.insert(15, "Cherry");
    assert(tree.isBalanced());

    assert(tree[10] == "Apple");
    assert(tree[5] == "Banana");
    assert(tree[15] == "Cherry");

    tree.insert(10, "Orange");

    assert(tree[10] == "Orange");

    tree.insert(10, "Grapes", [](const std::string &oldInfo, const std::string &newInfo)
                { return oldInfo + newInfo; });

    assert(tree[10] == "OrangeGrapes");

    cout << "All tests insert and get tests passed" << endl;
}

void testRemove()
{
    // Create an AVL tree and insert elements
    avl_tree<int, std::string> tree;
    tree.insert(10, "A");
    tree.insert(5, "B");
    tree.insert(15, "C");
    tree.insert(2, "D");
    tree.insert(8, "E");
    tree.insert(12, "F");
    tree.insert(18, "G");

    // Test removal of a node with no children
    assert(tree.remove(2));
    assert(!tree.find(2));     // The node with key 2 should not be found
    assert(tree.isBalanced()); // Verify that the tree is still balanced

    // Test removal of a node with one child
    assert(tree.remove(5));
    assert(!tree.find(5));     // The node with key 5 should not be found
    assert(tree.isBalanced()); // Verify that the tree is still balanced

    // Test removal of a node with two children
    assert(tree.remove(15));
    assert(!tree.find(15));    // The node with key 15 should not be found
    assert(tree.isBalanced()); // Verify that the tree is still balanced

    // Test removal of a non-existing node
    assert(!tree.remove(100)); // Node with key 100 doesn't exist, removal should fail
    assert(tree.isBalanced()); // Verify that the tree is still balanced

    // Add more tests as needed
}

int main()
{

    test_insert_find();
    test_insert_get();
    testRemove();
    cout << "All tests passed!" << endl;
    // avl_tree<int, int> my_first_tree;

    // my_first_tree.insert(10, 0);
    // my_first_tree.insert(9, 0);
    // my_first_tree.insert(8, 0);
    // my_first_tree.insert(7, 0);
    // my_first_tree.insert(6, 0);
    // my_first_tree.insert(5, 0);
    // my_first_tree.insert(4, 0);
    // my_first_tree.insert(3, 0);
    // my_first_tree.insert(2, 0);
    // my_first_tree.insert(1, 0);

    // my_first_tree.insert(11, 0);
    // my_first_tree.insert(12, 0);
    // assert(my_first_tree.isBalanced());

    // cout << "Start printing" << endl;
    // cout << my_first_tree << endl;
    // cout << "Oparetion 1 done" << endl;

    // my_first_tree.remove(10);
    // assert(my_first_tree.isBalanced());
    // my_first_tree.remove(9);
    // assert(my_first_tree.isBalanced());
    // my_first_tree.remove(8);
    // assert(my_first_tree.isBalanced());
    // my_first_tree.remove(7);
    // assert(my_first_tree.isBalanced());
    // my_first_tree.remove(3);
    // assert(my_first_tree.isBalanced());

    // cout << "Start printing" << endl;
    // cout << my_first_tree << endl;
    // cout << "Oparetion 2 done" << endl;
}