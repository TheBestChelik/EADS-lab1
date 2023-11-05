#include "Sequence.hpp"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void testPoppingPushingElements()
{
    // Test push_front, pop front methods
    Sequence<int, std::string> sequence1 = Sequence<int, std::string>();

    assert(sequence1.isEmpty());
    assert(sequence1.getLength() == 0);

    sequence1.push_front(1, "One");
    assert(!sequence1.isEmpty());
    assert(sequence1.getLength() == 1);

    sequence1.push_front(2, "Two");
    assert(sequence1.getLength() == 2);
    assert(!sequence1.isEmpty());

    sequence1.pop_front();
    assert(sequence1.getLength() == 1);
    assert(!sequence1.isEmpty());

    sequence1.pop_front();
    assert(sequence1.getLength() == 0);
    assert(sequence1.isEmpty());

    // Test push_back, pop_back method
    Sequence<int, std::string> sequence2;

    sequence2.push_back(1, "One");
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 1);

    sequence2.push_back(2, "Two");
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 2);

    sequence2.pop_back();
    assert(!sequence2.isEmpty());
    assert(sequence2.getLength() == 1);

    sequence2.clear();
    assert(sequence2.getLength() == 0);
    assert(sequence2.isEmpty());

    cout
        << "Push front and push back tests passed successfully!" << endl;
}

void testIterator()
{
    // Create a sample sequence
    Sequence<int, std::string> sequence;
    sequence.push_back(1, "One");
    sequence.push_back(2, "Two");
    sequence.push_back(3, "Three");
    sequence.push_back(4, "Four");

    // Test Iterator methods and begin(), end() methods
    Sequence<int, std::string>::Iterator it = sequence.begin();
    Sequence<int, std::string>::Iterator endIterator = sequence.end();

    // Test equality and inequality operators
    assert(it == sequence.begin());
    assert(it.key() == 1);
    assert(it.info() == "One");
    assert(endIterator == sequence.end());
    assert(it != endIterator);
    assert(endIterator.info() == "Four");
    assert(endIterator.key() == 4);

    // Test copyconstructor

    Sequence<int, std::string>::Iterator copiedIterator = Sequence<int, std::string>::Iterator(it);

    assert(copiedIterator.key() == it.key());

    assert(copiedIterator == it);

    // Test prefix increment operator (++)
    ++it;
    assert(it.key() == 2);
    assert(it.info() == "Two");

    // Test postfix increment operator (++)
    it++;
    assert(it.key() == 3);
    assert(it.info() == "Three");

    // Test addition operator (+)
    it = it + 1;
    assert(it.key() == 4);
    assert(it.info() == "Four");

    assert(it == endIterator);

    // Test addition operator (+) with some interval
    copiedIterator = copiedIterator + 4;
    assert(copiedIterator == it);

    // Test incrementing the ending iterator
    it = it + 1;
    assert(it.key() == 4);
    assert(it.info() == "Four");

    std::cout
        << "All iterator tests passed successfully!" << std::endl;
}

int main()
{

    testPoppingPushingElements();
    testIterator();
    cout
        << "End of tests!" << endl;
}