#include "avl_tree.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_insert_find()
{
    avl_tree<int, std::string> tree;

    // Test 1: Inserting elements into the tree
    tree.insert(10, "Apple");
    tree.insert(5, "Banana");
    tree.insert(15, "Cherry");

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

int main()
{

    test_insert_find();
    test_insert_get();
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

    // cout << "Start printing" << endl;
    // cout << my_first_tree << endl;
    // cout << "Oparetion done" << endl;
}