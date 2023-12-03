#include "bi_ring.h"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

void insert_test()
{

    BiRing<int, std::string> ring;

    // Insert at the beginning
    auto it1 = ring.insert(ring.cbegin(), 1, "one");
    assert(ring.getLength() == 1);
    assert(it1.key() == 1);
    assert(it1.info() == "one");

    // Insert at the end
    auto it2 = ring.insert(ring.cend(), 3, "three");
    assert(ring.getLength() == 2);
    assert(it2.key() == 3);
    assert(it2.info() == "three");

    // Insert in the middle (before it2)
    auto it3 = ring.insert(++ring.cbegin(), 2, "two");
    assert(ring.getLength() == 3);
    assert(it3.key() == 2);
    assert(it3.info() == "two");

    // Test sequence
    auto it = ring.cbegin();
    for (int i = 1; i <= 3; i++)
    {
        assert(it.key() == i);
        it++;
    }

    cout << "Insert tests passed" << endl;
}

void push_front_test()
{
    BiRing<int, std::string> ring;

    // Push at the front
    ring.push_front(1, "one");
    assert(ring.getLength() == 1);
    assert(ring.begin().key() == 1);
    assert(ring.begin().info() == "one");

    // Push more at the front
    ring.push_front(0, "zero");
    assert(ring.getLength() == 2);
    assert(ring.begin().key() == 0);
    assert(ring.begin().info() == "zero");
    assert((++ring.begin()).key() == 1);
    assert((++ring.begin()).info() == "one");

    cout << "Push Front tests passed" << endl;
}

void push_back_test()
{
    BiRing<int, std::string> ring;

    // Push at the back
    ring.push_back(3, "three");
    assert(ring.getLength() == 1);
    assert(ring.begin().key() == 3);
    assert(ring.begin().info() == "three");

    // Push more at the back
    ring.push_back(4, "four");
    assert(ring.getLength() == 2);
    assert(ring.begin().key() == 3);
    assert(ring.begin().info() == "three");
    assert((++ring.begin()).key() == 4);
    assert((++ring.begin()).info() == "four");

    cout << "Push Back tests passed" << endl;
}

void erase_test()
{
    BiRing<int, std::string> ring;
    ring.insert(ring.cend(), 1, "one");
    ring.insert(ring.cend(), 2, "two");
    ring.insert(ring.cend(), 3, "three");

    // Erase from the middle
    auto it5 = ++ring.cbegin();
    assert(it5.key() == 2);
    auto it6 = ring.erase(it5);
    assert(ring.getLength() == 2);
    assert(it6 == --ring.end());

    // Erase from the beginning
    auto it1 = ring.cbegin();
    assert(it1.key() == 1);
    auto it2 = ring.erase(it1);
    assert(ring.getLength() == 1);
    assert(it2.key() == 3);

    // Erase from the end
    auto it3 = --ring.cend();
    assert(it3.key() == 3);
    auto it4 = ring.erase(it3);
    assert(ring.getLength() == 0);
    assert(it4 == ring.end());
    assert(it4 == ring.begin());

    cout << "Erase tests passed" << endl;
}

void pop_front_test()
{
    BiRing<int, std::string> ring;
    ring.push_back(1, "one");
    ring.push_back(2, "two");

    // Pop from the front
    auto it1 = ring.cbegin();
    assert(it1.key() == 1);
    auto it2 = ring.pop_front();
    assert(ring.getLength() == 1);
    assert(it2 == ring.begin());
    assert(it2.key() == 2);
    assert(it2.info() == "two");

    // Pop more from the front
    auto it3 = ring.cbegin();
    assert(it3.key() == 2);
    auto it4 = ring.pop_front();
    assert(ring.getLength() == 0);
    assert(it4 == ring.end());

    // Pop from an empty ring
    BiRing<int, std::string> emptyRing;
    auto it5 = emptyRing.pop_front();
    assert(emptyRing.getLength() == 0);
    assert(it5 == emptyRing.end());

    cout << "Pop Front tests passed" << endl;
}

void pop_back_test()
{
    BiRing<int, std::string> ring;
    ring.push_back(2, "two");
    ring.push_back(3, "three");

    // Pop from the back
    auto it1 = --ring.cend();
    assert(it1.key() == 3);
    auto it2 = ring.pop_back();
    assert(ring.getLength() == 1);
    assert(it2.key() == 2);
    assert(it2.info() == "two");

    // Pop more from the back
    auto it3 = --ring.cend();
    assert(it3.key() == 2);
    auto it4 = ring.pop_back();
    assert(ring.getLength() == 0);
    assert(it4 == ring.end());

    // Pop from an empty ring
    BiRing<int, std::string> emptyRing;
    auto it5 = emptyRing.pop_back();
    assert(emptyRing.getLength() == 0);
    assert(it5 == emptyRing.end());

    cout << "Pop Back tests passed" << endl;
}

void clear_test()
{
    BiRing<int, std::string> ring;
    ring.push_back(1, "one");
    ring.push_back(2, "two");
    ring.push_back(3, "three");

    assert(ring.getLength() == 3);
    ring.clear();
    assert(ring.getLength() == 0);
    assert(ring.isEmpty() == true);

    ring.clear(); // clearing empty ring
    assert(ring.isEmpty() == true);

    cout << "Clear test passed" << endl;
}

void copy_constructor_test()
{
    // Original ring
    BiRing<int, std::string> originalRing;
    originalRing.push_back(1, "one");
    originalRing.push_back(2, "two");
    originalRing.push_back(3, "three");

    // Copy constructor
    BiRing<int, std::string> copiedRing(originalRing);

    // Test the size of the copied ring
    assert(copiedRing.getLength() == originalRing.getLength());

    // Test the content of the copied ring
    auto originalIt = originalRing.cbegin();
    auto copiedIt = copiedRing.cbegin();
    while (originalIt != originalRing.cend() && copiedIt != copiedRing.cend())
    {
        assert(originalIt.key() == copiedIt.key());
        assert(originalIt.info() == copiedIt.info());

        originalIt.next();
        copiedIt.next();
    }

    // Test the end iterator of the copied ring
    assert(copiedIt == copiedRing.cend());

    originalRing.clear();
    assert(originalRing.isEmpty() == true);
    assert(copiedRing.getLength() == 3);

    cout
        << "Copy Constructor tests passed" << endl;
}

void iterator_increment_test()
{
    BiRing<int, std::string> originalRing;
    originalRing.push_back(1, "A");
    originalRing.push_back(2, "A");
    originalRing.push_back(3, "A");
    originalRing.push_back(4, "A");
    originalRing.push_back(5, "A");
    originalRing.push_back(6, "A");
    originalRing.push_back(7, "A");

    int i = 1;
    for (auto it = originalRing.cbegin(); it != originalRing.cend(); it.next())
    {
        assert(it.key() == i);
        i++;
    }

    auto it = originalRing.begin();
    for (int i = 1; i <= 7; i++)
    {
        assert(it.key() == i);
        it++;
    }
    // jumping over sentinel
    assert(it.key() == 1);

    auto end = --originalRing.cend();
    end.next();
    assert(end.key() == 0); // sentinel node, default key is 0

    cout << "Iterator increment tests passed" << endl;
}

void iterator_decrement_test()
{
    BiRing<int, std::string> originalRing;
    originalRing.push_back(1, "A");
    originalRing.push_back(2, "A");
    originalRing.push_back(3, "A");
    originalRing.push_back(4, "A");
    originalRing.push_back(5, "A");
    originalRing.push_back(6, "A");
    originalRing.push_back(7, "A");

    int i = 7;
    for (auto it = --originalRing.cend(); it != originalRing.cbegin(); it.prev())
    {
        assert(it.key() == i);
        i--;
    }

    auto it = --originalRing.end();
    for (int i = 7; i >= 1; i--)
    {
        assert(it.key() == i);
        it--;
    }

    // Jumping over sentinel
    assert(it.key() == 7);

    auto begin = originalRing.cbegin();
    begin.prev();
    assert(begin.key() == 0); // Sentinel node, default key is 0

    cout << "Iterator decrement tests passed" << endl;
}

void find_key_test()
{
    BiRing<int, std::string> ring;
    ring.push_back(1, "One");
    ring.push_back(2, "Two");
    ring.push_back(3, "Three");
    ring.push_back(3, "SecondThree");
    ring.push_back(4, "Four");
    ring.push_back(3, "ThirdThree");
    ring.push_back(5, "Five");

    // Test with modifying_iterator
    {
        auto it = ring.begin();
        auto search_from = ring.begin();
        auto search_till = ring.end();

        bool found = ring.find_key(it, 3, search_from, search_till);

        assert(found);
        assert(it.key() == 3);
        assert(it.info() == "Three");
    }

    // Test with constant_iterator
    {
        auto it = ring.cbegin();
        auto search_from = ring.cbegin();
        auto search_till = ring.cend();

        bool found = ring.find_key(it, 3, search_from, search_till);

        assert(found);
        assert(it.key() == 3);
        assert(it.info() == "Three");
    }

    // Search_from is after search_till
    cout << "Reversed search" << endl;
    {
        auto it = ring.begin();
        auto search_from = --ring.end();
        assert(search_from.key() == 5);
        auto search_till = search_from - 1;
        assert(search_till.key() == 3);

        bool found = ring.find_key(it, 4, search_from, search_till);

        assert(found == true);
        assert(it.key() == 4);
        assert(it.info() == "Four");
    }

    // Test with a key that doesn't exist
    {
        auto it = ring.begin();
        auto search_from = ring.begin();
        auto search_till = ring.end();

        bool found = ring.find_key(it, 99, search_from, search_till);

        assert(!found);
    }

    // Finding different occurrences
    {

        std::string Infos[] = {"Three", "SecondThree", "ThirdThree"};
        auto it = ring.begin();
        auto search_from = ring.begin();
        auto search_till = ring.end();
        int i = 0;
        while (ring.find_key(it, 3, search_from, search_till))
        {
            search_from = it + 1;
            assert(it.key() == 3);
            assert(it.info() == Infos[i]);
            i++;
        }
    }

    cout << "Find key tests passed" << endl;
}

void iterator_operators_test()
{
    BiRing<int, std::string> originalRing;
    originalRing.push_back(1, "A");
    originalRing.push_back(2, "A");
    originalRing.push_back(3, "A");
    originalRing.push_back(4, "A");
    originalRing.push_back(5, "A");
    originalRing.push_back(6, "A");
    originalRing.push_back(7, "A");

    auto it = originalRing.begin();
    it = it + 3;
    assert(it.key() == 4);
    it = it - 2;
    assert(it.key() == 2);
    it = it + originalRing.getLength();
    assert(it.key() == 2);
    it = it + 1000 * originalRing.getLength();
    assert(it.key() == 2);
    it = it + 1000 * originalRing.getLength() - 1;
    assert(it.key() == 1);
    it = it - originalRing.getLength();
    assert(it.key() == 1);
    it = it - 1000 * originalRing.getLength();
    assert(it.key() == 1);
    it = it - 1000 * originalRing.getLength() - 1;
    assert(it.key() == 7);

    cout << "Iterator operator tests passed" << endl;
}

void occurrencesOf_test()
{
    BiRing<int, std::string> ring;
    ring.push_back(1, "One");
    ring.push_back(2, "Two");
    ring.push_back(1, "One");
    ring.push_back(3, "Three");
    ring.push_back(1, "One");
    ring.push_back(4, "Four");

    {
        unsigned int count = ring.occurrencesOf(1);
        assert(count == 3);
    }

    // Test with a key that doesn't exist
    {
        unsigned int count = ring.occurrencesOf(99);
        assert(count == 0);
    }

    // Test with an empty ring
    {
        BiRing<int, std::string> emptyRing;
        unsigned int count = emptyRing.occurrencesOf(1);
        assert(count == 0);
    }

    // Test with a complex key (assuming Key supports ==)
    {
        BiRing<std::pair<int, char>, std::string> complexRing;
        complexRing.push_back({1, 'a'}, "Pair A");
        complexRing.push_back({2, 'b'}, "Pair B");
        complexRing.push_back({1, 'a'}, "Pair A");

        unsigned int count = complexRing.occurrencesOf({1, 'a'});
        assert(count == 2);
    }

    cout << "OccurrencesOf tests passed" << endl;
}

int main()
{
    cout << "Start of tests" << endl;

    iterator_increment_test();

    iterator_decrement_test();

    insert_test();

    push_back_test();

    push_front_test();

    erase_test();

    pop_front_test();

    pop_back_test();

    clear_test();

    copy_constructor_test();

    find_key_test();

    iterator_operators_test();

    occurrencesOf_test();

    cout
        << "All tests have passed!" << endl;
}