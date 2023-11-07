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

// Copy constructor
template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &src)
{
    // Use the copy assignment operator to copy elements from src to *this
    *this = src;
}

// Copy assignment operator using iterators
template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &src)
{
    if (this != &src)
    {
        // Clear the current sequence
        clear();
        auto it = src.begin();
        // Copy elements from src to this using iterators
        for (int i = 0; i < src.getLength(); i++)
        {
            push_back(it.key(), it.info());
            it++;
        }
    }
    return *this;
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
    Node *newNode = new Node(key, info, nullptr);
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

// begin method
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::begin() const
{
    return Iterator(head);
}

// end method
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::end() const
{
    return Iterator(tail);
}

// Iterator assignment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator &Sequence<Key, Info>::Iterator::operator=(const Iterator &src)
{
    if (this != &src)
    {
        current = src.current;
    }
    return *this;
}

// Iterator copyconstructor
template <typename Key, typename Info>
Sequence<Key, Info>::Iterator::Iterator(const Iterator &src)
{
    this->current = src.current;
}

// Iterator equality operator
template <typename Key, typename Info>
bool Sequence<Key, Info>::Iterator::operator==(const Iterator &src) const
{
    return current == src.current;
}

// Iterator inequality operator
template <typename Key, typename Info>
bool Sequence<Key, Info>::Iterator::operator!=(const Iterator &src) const
{
    return current != src.current;
}

// Iterator prefix increment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator &Sequence<Key, Info>::Iterator::operator++()
{
    if (current == nullptr)
    {
        throw std::runtime_error("Iterator is null");
    }
    if (current->next != nullptr)
    {
        current = current->next;
    }
    return *this;
}

// Iterator postfix increment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::Iterator::operator++(int)
{
    if (current == nullptr)
    {
        throw std::runtime_error("Iterator is null");
    }
    Iterator temp = *this;
    if (current->next != nullptr)
    {
        current = current->next;
    }
    return temp;
}

// Iterator addition operator for advancing the iterator by a specified interval
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::Iterator::operator+(int interval)
{
    if (current == nullptr)
    {
        throw std::runtime_error("Iterator is null");
    }
    Iterator temp = *this;
    while (interval > 0 && temp.current->next != nullptr)
    {
        temp++;
        interval--;
    }
    return temp;
}

// Iterator key accessor
template <typename Key, typename Info>
Key &Sequence<Key, Info>::Iterator::key() const
{
    if (current == nullptr)
    {
        throw std::runtime_error("Iterator is null");
    }
    return current->key;
}

// Iterator info accessor
template <typename Key, typename Info>
Info &Sequence<Key, Info>::Iterator::info() const
{
    if (current == nullptr)
    {
        throw std::runtime_error("Iterator is null");
    }
    return current->info;
}

// get Node method
template <typename Key, typename Info>
typename Sequence<Key, Info>::Node *Sequence<Key, Info>::getNode(const Key &key, unsigned int occurrence)
{
    Node *currentNode = head;
    unsigned int count = 0;

    while (currentNode != nullptr)
    {
        if (currentNode->key == key)
        {
            count++;
            if (count == occurrence)
            {
                // Found the node with the specified key and occurrence
                return currentNode;
            }
        }
        currentNode = currentNode->next;
    }

    // Node with the specified key and occurrence not found
    return nullptr;
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::occurrencesOf(const Key &key) const
{
    Node *currentNode = head;
    unsigned int count = 0;

    while (currentNode != nullptr)
    {
        if (currentNode->key == key)
        {
            // Found an occurrence of the specified key
            count++;
        }
        currentNode = currentNode->next;
    }

    // Return the total number of occurrences of the specified key
    return count;
}

// exists method
template <typename Key, typename Info>
bool Sequence<Key, Info>::exists(const Key &key, unsigned int occurrence) const
{
    return occurrencesOf(key) != 0;
}

// find method
template <typename Key, typename Info>
bool Sequence<Key, Info>::find(Iterator &it, const Key &key, unsigned int occurrence)
{
    Node *foundNode = getNode(key, occurrence);

    if (foundNode != nullptr)
    {
        // Update the provided Iterator to point to the found element
        it = Iterator(foundNode);
        return true; // Element found
    }

    // Element not found
    return false;
}

// find node before given
template <typename Key, typename Info>
typename Sequence<Key, Info>::Node *Sequence<Key, Info>::getNodeBefore(const Key &key, unsigned int occurrence)
{
    Node *previousNode = nullptr;
    Node *currentNode = head;
    unsigned int count = 0;

    while (currentNode != nullptr)
    {
        if (currentNode->key == key)
        {
            count++;
            if (count == occurrence)
            {
                // Found the node with the specified key and occurrence
                // Return the node before this node (previousNode)
                return previousNode;
            }
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // Node before the specified key and occurrence not found
    return nullptr;
}

// find before method
template <typename Key, typename Info>
bool Sequence<Key, Info>::findBefore(Iterator &it, const Key &key, unsigned int occurrence)
{
    Node *beforeNode = getNodeBefore(key, occurrence);

    if (beforeNode != nullptr)
    {
        // Update the provided Iterator to point to the node before the found element
        it = Iterator(beforeNode);
        return true; // Element found
    }

    // Element not found
    return false;
}

// insert after method
template <typename Key, typename Info>
bool Sequence<Key, Info>::insert_after(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence)
{
    Node *targetNode = getNode(target_key, occurrence);

    if (targetNode == nullptr)
    {
        return false; // Target element not found
    }

    Node *newNode = new Node(key, info, targetNode->next);
    targetNode->next = newNode;
    if (targetNode == tail)
    {
        tail = newNode; // Update tail if targetNode is the last node
    }
    length++;
    return true; // Element inserted successfully
}

// insert before method
template <typename Key, typename Info>
bool Sequence<Key, Info>::insert_before(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence)
{

    if (!exists(target_key, occurrence))
    {
        return false;
    }
    Node *beforeNode = getNodeBefore(target_key, occurrence);

    if (beforeNode == nullptr)
    {
        // required element is the first element in the sequence
        push_front(key, info);
    }
    else
    {
        Node *newNode = new Node(key, info, beforeNode->next);
        beforeNode->next = newNode;
        length++;
    }

    return true; // Element inserted successfully
}

// remove method
template <typename Key, typename Info>
bool Sequence<Key, Info>::remove(const Key &key, unsigned int occurrence)
{

    if (!exists(key, occurrence))
    {
        return false;
    }

    Node *beforeNode = getNodeBefore(key, occurrence);

    if (beforeNode == nullptr)
    {
        // required element is the first element in the sequence
        pop_front();
    }
    else
    {
        Node *targetNode = beforeNode->next;
        beforeNode->next = targetNode->next;
        if (targetNode == tail)
        {
            tail = beforeNode; // Update tail if targetNode is the last node
        }
        delete targetNode;
        length--;
    }
    return true; // Element removed successfully
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
