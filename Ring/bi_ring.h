#include <iostream>

using namespace std;

template <typename Key, typename Info>
class BiRing
{
private:
    class Node
    {
    private:
        Node *next;
        Node *prev;

    public:
        Key key;
        Info info;

        Node(const Key &_key, const Info &_info, Node *_next = nullptr, Node *_prev = nullptr)
            : key(_key), info(_info), next(_next), prev(_prev) {}

        friend class BiRing;
    };

    template <typename KeyType, typename InfoType, typename RingType>
    class Iterator
    {
    private:
        friend class BiRing;

        Node *ptr;
        const RingType &ring;

        Iterator(Node *ptr, const RingType &ring) : ptr(ptr), ring(ring) {}

    public:
        bool operator==(const Iterator &other) const
        {
            return ptr == other.ptr;
        }

        bool operator!=(const Iterator &other) const
        {
            return ptr != other.ptr;
        }

        Iterator &operator=(const Iterator &src)
        {
            if (this != &src)
            {
                ptr = src.ptr;
            }
            return *this;
        }

        Iterator operator+(int steps) const
        {
            Iterator result = *this;
            for (int i = 0; i < steps % ring.length; ++i)
            {
                result++;
            }
            return result;
        }

        Iterator operator-(int steps) const
        {
            Iterator result = *this;
            for (int i = 0; i < steps % ring.length; ++i)
            {
                result--;
            }
            return result;
        }

        Iterator operator++()
        {
            next();
            if (ptr == ring.sentinel)
            {
                // skipping sentinel
                next();
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            next();
            if (ptr == ring.sentinel)
            {
                // skipping sentinel
                next();
            }
            return temp;
        }

        Iterator operator--()
        {
            prev();
            if (ptr == ring.sentinel)
            {
                // skip sentinel
                prev();
            }

            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            prev();
            if (ptr == ring.sentinel)
            {
                // skip sentinel
                prev();
            }

            return temp;
        }

        Iterator next()
        {
            if (ptr == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            ptr = ptr->next;
            return *this;
        }

        Iterator prev()
        {
            if (ptr == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }

            ptr = ptr->prev;
            return *this;
        }

        KeyType &key() const
        {
            return ptr->key;
        }

        InfoType &info() const
        {
            return ptr->info;
        }
    };

    unsigned int length;

    Node *sentinel;

public:
    typedef Iterator<Key, Info, BiRing> modifying_iterator;
    typedef Iterator<const Key, const Info, BiRing> constant_iterator;

    BiRing() : length(0)
    {
        sentinel = new Node(Key(), Info(), nullptr, nullptr);
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    };
    BiRing(const BiRing &src) : length(0)
    {
        sentinel = new Node(Key(), Info(), nullptr, nullptr);
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        *this = src;
    };
    ~BiRing()
    {
        clear();
        delete sentinel;
    };
    BiRing &operator=(const BiRing &src)
    {
        if (this != &src)
        {
            clear();
            // Copy elements from src to this using iterators
            for (auto it = src.cbegin(); it != src.cend(); it.next())
            {

                push_back(it.key(), it.info());
            }
        }
        return *this;
    };

    /**
     * @brief Get the Length of ring
     *
     * @return int len of ring
     */
    unsigned int getLength() const
    {
        return length;
    };

    /**
     * Checks if ring is empty
     *
     * @return true if ring is empty
     * @return false if ring is not empty
     */
    bool isEmpty() const
    {
        return length == 0;
    };

    /**
     * Inserts a new element with the provided key and info before the specified node
     * on which iterator os pointing at.
     *
     * @param position Iterator pointing on node before which the new node has to be inserted
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @return iterator pointing on inserted node
     */
    modifying_iterator insert(constant_iterator position, const Key &key, const Info &info)
    {
        Node *newNode = new Node(key, info, nullptr, nullptr);

        Node *positionNode = position.ptr;
        newNode->next = positionNode;
        newNode->prev = positionNode->prev;
        positionNode->prev->next = newNode;
        positionNode->prev = newNode;

        length++;

        return modifying_iterator(newNode, *this);
    }

    /**
     * Removes the specified element.
     *
     * @param position constant iterator pointing on element to be erased.
     * @return modifying_iterator pointing on next element after deleted
     */
    modifying_iterator erase(constant_iterator position)
    {
        if (position == cend())
        {
            // If the iterator points to the end, nothing to erase
            return end();
        }

        Node *eraseNode = position.ptr;
        Node *nextNode = eraseNode->next;

        eraseNode->prev->next = eraseNode->next;
        eraseNode->next->prev = eraseNode->prev;

        delete eraseNode;

        length--;

        return modifying_iterator(nextNode, *this);
    };

    /**
     * @brief clears the ring
     *
     */
    void clear()
    {
        while (!isEmpty())
        {
            pop_back();
        }
    };

    /**
     * Searches for the specified element of a given key.
     *
     * @param [out] it is modifying iterator pointing on found element
     * @param key The key to search for.
     * @param search_from iterator pointing on element from which start searching
     * @param search_till iterator pointing on element until which element to search
     * @return true if element found
     * @return false if element not found
     */
    template <typename iterator>
    bool find_key(iterator &it, const Key &key,
                  iterator &search_from,
                  iterator &search_till) const
    {
        for (; search_from != search_till; search_from.next())
        {
            if (search_from.ptr == sentinel)
            {
                continue;
            }
            if (search_from.key() == key)
            {
                it = search_from;
                return true;
            }
        }
        return false;
    };

    /**
     * @brief number of occurrences of key
     *
     * @param key is key which occurrences we count
     * @return unsigned int number of occurrences of key
     */
    unsigned int occurrencesOf(const Key &key) const
    {
        unsigned int counter = 0;
        for (auto it = cbegin(); it != cend(); it.next())
        {
            if (it.key() == key)
            {
                counter++;
            }
        }
        return counter;
    };

    /**
     * @brief inserts element in the beginning of the ring
     *
     * @param key is the key that will be inserted
     * @param info is info that will be inserted
     * @return iterator pointing on inserted element
     */
    modifying_iterator push_front(const Key &key, const Info &info)
    {
        return insert(cbegin(), key, info);
    };

    /**
     * @brief inserts element in the end of the ring
     *
     * @param key is the key that will be inserted
     * @param info is info that will be inserted
     * @return iterator pointing on inserted element
     */
    modifying_iterator push_back(const Key &key, const Info &info)
    {
        return insert(cend(), key, info);
    };

    /**
     * @brief erases first element in the ring
     *
     * @return Iterator pointing on next element after deleted
     */
    modifying_iterator pop_front()
    {
        return erase(cbegin());
    };

    /**
     * @brief erases last element in the ring
     *
     * @return Iterator pointing on next element before deleted
     */
    modifying_iterator pop_back()
    {
        return --erase(--cend());
    };

    /**
     * @brief returns iterator pointing on first element of the ring
     *
     * @return modifying_iterator
     */
    modifying_iterator begin()
    {
        return modifying_iterator(sentinel->next, *this);
    };

    /**
     * @brief returns constant iterator pointing on first element of the ring
     *
     * @return constant_iterator
     */
    constant_iterator cbegin() const
    {
        return constant_iterator(sentinel->next, *this);
    };

    /**
     * @brief returns iterator pointing on the last element of the ring
     *
     * @return modifying_iterator
     */
    modifying_iterator end()
    {
        return modifying_iterator(sentinel, *this);
    };

    /**
     * @brief return the constant iterator pointing on the last element of the ring
     *
     * @return constant_iterator
     */
    constant_iterator cend() const
    {
        return constant_iterator(sentinel, *this);
    };
};

//////EXTERNAL FUNCTIONS///////////////
template <typename Key, typename Info>
BiRing<Key, Info> filter(const BiRing<Key, Info> &source, bool (*pred)(const Key &))
{
    BiRing<Key, Info> result;

    for (auto it = source.cbegin(); it != source.cend(); it.next())
    {
        if (pred(it.key()))
        {
            result.push_back(it.key(), it.info());
        }
    }

    return result;
}

template <typename Key, typename Info>
BiRing<Key, Info> unique(const BiRing<Key, Info> &src, Info (*aggregate)(const Key &, const Info &, const Info &))
{
    BiRing<Key, Info> result;

    for (auto it = src.cbegin(); it != src.cend(); it.next())
    {
        auto search_res = result.cbegin();
        auto sf = result.cbegin();
        auto st = result.cend();
        Key key = it.key();
        if (result.find_key(search_res, key, sf, st))
        {
            continue;
        }
        auto searching_it = src.cbegin();
        auto search_from = it;
        search_from.next();
        auto search_till = src.cend();
        Info new_info = it.info();
        while (src.find_key(searching_it, key, search_from, search_till))
        {
            new_info = aggregate(key, new_info, searching_it.info());
            search_from.next();
        }
        result.push_back(it.key(), new_info);
    }
    return result;
}

template <typename Key, typename Info>
Info sum_info(const Key &, const Info &i1, const Info &i2)
{
    return i1 + i2;
}
template <typename Key, typename Info>
BiRing<Key, Info> join(const BiRing<Key, Info> &first, const BiRing<Key, Info> &second)
{
    BiRing<Key, Info> pre_result = first;
    for (auto it = second.cbegin(); it != second.cend(); it.next())
    {
        pre_result.push_back(it.key(), it.info());
    }
    return unique(pre_result, sum_info<Key, Info>);
}

template <typename Key, typename Info>
BiRing<Key, Info> shuffle(
    const BiRing<Key, Info> &first, unsigned int fcnt,
    const BiRing<Key, Info> &second, unsigned int scnt,
    unsigned int reps)
{
    BiRing<Key, Info> result;

    auto first_it = first.cbegin();
    auto second_it = second.cbegin();

    for (unsigned int rep = 0; rep < reps; rep++)
    {
        for (unsigned int i = 0; i < fcnt; i++)
        {
            result.push_back(first_it.key(), first_it.info());

            first_it++;
        }

        for (unsigned int i = 0; i < scnt; i++)
        {
            result.push_back(second_it.key(), second_it.info());

            second_it++;
        }
    }

    return result;
}