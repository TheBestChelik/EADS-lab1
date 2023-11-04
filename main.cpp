#include "Sequence.hpp"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void testAddingElements()
{
    // Test push_front method
    Sequence<int, std::string> sequence1 = Sequence<int, std::string>();
    sequence1.push_front(1, "One");
    assert(!sequence1.isEmpty());
    assert(sequence1.getLength() == 1);

    sequence1.push_front(2, "Two");
    assert(sequence1.getLength() == 2);

    // Verify elements and order after push_front
    // int key;
    // std::string info;
    // // assert(sequence1.get_info(info, key));
    // assert(key == 2);
    // assert(info == "Two");

    sequence1.pop_front();
    assert(sequence1.getLength() == 1);
    // assert(sequence1.get_info(info, key));
    // assert(key == 1);
    // assert(info == "One");

    // Test push_back method
    Sequence<int, std::string> sequence2;
    sequence2.push_back(1, "One");
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 1);

    sequence2.push_back(2, "Two");
    assert(sequence2.getLength() == 2);

    sequence2.pop_back();
    assert(sequence2.getLength() == 1);

    sequence2.clear();
    assert(sequence2.isEmpty());

    // // Verify elements and order after push_back
    // assert(sequence2.get_info(info, key));
    // assert(key == 1);
    // assert(info == "One");

    // sequence2.pop_front(); // Remove the first element
    // assert(sequence2.getLength() == 1);
    // assert(sequence2.get_info(info, key));
    // assert(key == 2);
    // assert(info == "Two");

    cout
        << "Push front and push back tests passed successfully!" << endl;
}

int main()
{
    testAddingElements();
    cout << "End of tests!" << endl;
}