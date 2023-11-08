#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Sequence;

template <typename Key, typename Info>
ostream &operator<<(ostream &os, const Sequence<Key, Info> &sequence)
{
    typename Sequence<Key, Info>::Iterator iter = sequence.begin();

    os << "[";
    for (auto it = sequence.begin(); it != sequence.empty(); it++)
    {
        os << "(" << iter.key() << ", " << iter.info() << ")";
        if (it != sequence.end())
        {
            os << ", ";
        }
    }
    os << "]";

    return os;
};

template <typename Key, typename Info>
void split_pos(/*const*/ Sequence<Key, Info> &seq, int start_pos, int len1, int len2, int count, Sequence<Key, Info> &seq1, Sequence<Key, Info> &seq2);

template <typename Key, typename Info>
void split_key(Sequence<Key, Info> &seq, const Key &start_key, int start_occ, int len1, int len2, int count, Sequence<Key, Info> &seq1, Sequence<Key, Info> &seq2);

template <typename Key, typename Info>
class Sequence
{
private:
    class Node
    {
    private:
        Node *next;

    public:
        Key key;
        Info info;

        Node(const Key &_key, const Info &_info, Node *_next)
            : key(_key), info(_info), next(_next) {}

        friend class Sequence;
    };

    Node *head;
    Node *tail;
    unsigned int length;

    // methods
    Node *getNode(const Key &key, unsigned int occurrence = 1)
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
    };
    Node *getNodeBefore(const Key &key, unsigned int occurrence = 1)
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
    };

public:
    Sequence() : head(nullptr), tail(nullptr), length(0){};
    ~Sequence()
    {
        clear();
    };
    Sequence(const Sequence &src)
    {
        *this = src;
    };
    Sequence &operator=(const Sequence &src)
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
    };

    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *ptr = nullptr) : current(ptr){};
        ~Iterator(){};
        Iterator(const Iterator &src)
        {
            this->current = src.current;
        };
        Iterator &operator=(const Iterator &src)
        {
            if (this != &src)
            {
                current = src.current;
            }
            return *this;
        };

        bool operator==(const Iterator &src) const
        {
            return current == src.current;
        };
        bool operator!=(const Iterator &src) const
        {
            return current != src.current;
        };

        Iterator &operator++()
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            if (current != nullptr)
            {
                current = current->next;
            }
            return *this;
        };
        Iterator operator++(int)
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            Iterator temp = *this;
            if (current != nullptr)
            {
                current = current->next;
            }
            return temp;
        };
        Iterator operator+(int interval)
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            Iterator temp = *this;
            while (interval > 0 && temp.current != nullptr)
            {
                temp++;
                interval--;
            }
            return temp;
        };

        Key &key() const
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            return current->key;
        };
        Info &info() const
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Iterator is null");
            }
            return current->info;
        };
    };

    int getLength() const
    {
        return length;
    };

    bool isEmpty() const
    {
        return length == 0;
    };

    /**
     * Inserts a new element with the provided key and info after the specified target element
     * of a given key and occurrence.
     *
     *
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @param target_key The key after which the new element should be inserted.
     * @param occurrence Specifies after which occurrence of `target_key` to insert.
     * @return true if the element was successfully inserted, false otherwise.
     */
    bool insert_after(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence = 1)
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
    };
    bool insert_before(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence = 1)
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
    };

    void push_front(const Key &key, const Info &info)
    {
        Node *newNode = new Node(key, info, head);
        head = newNode;
        if (tail == nullptr)
        {
            tail = newNode;
        }
        length++;
    };
    void push_back(const Key &key, const Info &info)
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
    };

    /**
     * Removes the specified element of a given key and occurrence.
     *
     * @param key The key of the element to remove.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @return true if an element was successfully removed, false otherwise.
     */
    bool remove(const Key &key, unsigned int occurrence = 1)
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
    };

    bool pop_front()
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
    };
    bool pop_back()
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
    };

    void clear()
    {
        while (pop_front())
        {
        }
    };

    /**
     * Searches for the specified element of a given key and occurrence.
     *
     * @param key The key to search for.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @return true if the specified element is found, false otherwise.
     */
    bool exists(const Key &key, unsigned int occurrence = 1) const
    {
        return occurrencesOf(key) != 0;
    };

    /**
     * Counts the number of occurrences of the given key.
     */
    unsigned int occurrencesOf(const Key &key) const
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
    };

    /**
     * Searches for the specified element of a given key and occurrence.
     *
     * @param key The key to search for.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @param [out] it is iterator pointing on found element
     * @return true if the specified element is found, false otherwise.
     */
    bool find(Iterator &it, const Key &key, unsigned int occurrence = 1)
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
    };

    /**
     * Searches for the specified element before element with given key and occurrence
     *
     * @param key The key to search for.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @param [out] it is iterator pointing on found element
     * @return true if the specified element is found, false otherwise.
     */
    bool findBefore(Iterator &it, const Key &key, unsigned int occurrence = 1)
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
    };

    /**
     * Returns first or last element of sequence
     *
     * @param [out] it is iterator pointing on found element
     * @return true if the specified element is found, false otherwise.
     */
    Iterator begin() const
    {
        return Iterator(head);
    };
    Iterator end() const
    {
        return Iterator(tail);
    };
    Iterator empty() const
    {
        return Iterator(nullptr);
    };
};

// operator<<
// sort
// reverse
// swap
// subSequence
#endif