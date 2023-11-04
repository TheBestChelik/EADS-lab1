#include "Sequence.hpp"
#include <iostream>

using namespace std;

template class Sequence<int, std::string>;

// Destructor
template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    clear();
}

// isEmpty method
template <typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty() const
{
    return length == 0;
}

// get length method
template <typename Key, typename Info>
int Sequence<Key, Info>::getLength() const
{
    return length;
}

// Push front method
template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key &key, const Info &info)
{
    Node *newNode = new Node(key, info, head);
    head = newNode;
    if (tail == nullptr)
    {
        tail = newNode;
    }
    length++;
}

// Push back method
template <typename Key, typename Info>
void Sequence<Key, Info>::push_back(const Key &key, const Info &info)
{
    Node *newNode = new Node(key, info);
    if (tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

// Pop back method
template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_back()
{
    if (isEmpty())
    {
        return false; // Sequence is empty, cannot pop back
    }

    if (head == tail)
    {
        // Sequence has only one element
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        // Traverse the list to find the second-to-last node
        Node *prevNode = nullptr;
        Node *currentNode = head;
        while (currentNode->next != nullptr)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        // Remove the last node (tail)
        delete tail;
        tail = prevNode;
        tail->next = nullptr;
    }

    length--;
    return true; // Successfully popped the last element
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_front()
{
    if (isEmpty())
    {
        return false; // Sequence is empty, cannot pop front
    }

    Node *temp = head;
    head = head->next;

    if (head == nullptr)
    {
        // If the sequence becomes empty after removal
        tail = nullptr;
    }

    delete temp;
    length--;
    return true; // Successfully popped the first element
}

// Clear method
template <typename Key, typename Info>
void Sequence<Key, Info>::clear()
{
    while (pop_front())
    {
    }
}

// Overloaded stream insertion operator
template <typename Key, typename Info>
std::ostream &operator<<(std::ostream &os, const Sequence<Key, Info> &sequence)
{
    typename Sequence<Key, Info>::Iterator iter = sequence.begin();

    os << "[";
    while (iter != sequence.end())
    {
        os << "(" << iter.key() << ", " << iter.info() << ")";
        ++iter;
        if (iter != sequence.end())
        {
            os << ", ";
        }
    }
    os << "]";

    return os;
}
