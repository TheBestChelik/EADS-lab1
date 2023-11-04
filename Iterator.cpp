#include "Sequence.hpp"

// Iterator constructor
template <typename Key, typename Info>
Sequence<Key, Info>::Iterator::Iterator(Node *ptr) : current(ptr) {}

// Destructor
template <typename Key, typename Info>
Sequence<Key, Info>::Iterator::~Iterator() {}

// Copy constructor
template <typename Key, typename Info>
Sequence<Key, Info>::Iterator::Iterator(const Iterator &src) : current(src.current) {}

// Assignment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator &Sequence<Key, Info>::Iterator::operator=(const Iterator &src)
{
    if (this != &src)
    {
        current = src.current;
    }
    return *this;
}

// Equality operator
template <typename Key, typename Info>
bool Sequence<Key, Info>::Iterator::operator==(const Iterator &src) const
{
    return current == src.current;
}

// Inequality operator
template <typename Key, typename Info>
bool Sequence<Key, Info>::Iterator::operator!=(const Iterator &src) const
{
    return current != src.current;
}

// Prefix increment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator &Sequence<Key, Info>::Iterator::operator++()
{
    if (current->next != nullptr)
    {
        current = current->next;
    }
    return *this;
}

// Postfix increment operator
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::Iterator::operator++(int)
{
    Iterator temp = *this;
    if (current->next != nullptr)
    {
        current = current->next;
    }
    return temp;
}

// Addition operator for advancing the iterator by a specified interval
template <typename Key, typename Info>
typename Sequence<Key, Info>::Iterator Sequence<Key, Info>::Iterator::operator+(int interval)
{
    Iterator temp = *this;
    while (interval > 0 && temp.current->next != nullptr)
    {
        temp.current = temp.current->next;
        interval--;
    }
    return temp;
}

// Key accessor
template <typename Key, typename Info>
Key &Sequence<Key, Info>::Iterator::key() const
{
    return current->key;
}

// Info accessor
template <typename Key, typename Info>
Info &Sequence<Key, Info>::Iterator::info() const
{
    return current->info;
}
