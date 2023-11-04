#include <iostream>

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

        Node(const Key &_key, const Info &_info, Node *_next = nullptr)
            : key(_key), info(_info), next(_next) {}

        friend class Sequence;
    };

    Node *head;
    Node *tail;
    unsigned int length;

    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *ptr = nullptr);
        ~Iterator();
        Iterator(const Iterator &src);
        Iterator &operator=(const Iterator &src);

        bool operator==(const Iterator &src) const;
        bool operator!=(const Iterator &src) const;

        Iterator &operator++();
        Iterator operator++(int);
        Iterator operator+(int interval);

        Key &key() const;
        Info &info() const;
    };

    // methods
    Node *getNode(const Key &key, unsigned int occurrence = 1);

public:
    Sequence() : head(nullptr), tail(nullptr), length(0){};
    ~Sequence();
    Sequence(const Sequence &src);
    Sequence &operator=(const Sequence &src);

    int getLength() const;
    bool isEmpty() const;

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
    bool insert_after(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence = 1);
    bool insert_before(const Key &key, const Info &info, const Key &target_key, unsigned int occurrence = 1);

    void push_front(const Key &key, const Info &info);
    void push_back(const Key &key, const Info &info);

    /**
     * Removes the specified element of a given key and occurrence.
     *
     * @param key The key of the element to remove.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @return true if an element was successfully removed, false otherwise.
     */
    bool remove(const Key &key, unsigned int occurrence = 1);

    bool pop_front();
    bool pop_back();

    void clear();

    /**
     *
     * Retrieves the info associated to a specified element of a given key and occurrence.
     *
     * @param[out] info Reference to where the info will be stored.
     * @param key The key for which to retrieve the associated info.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @return true if the element was found and the associated info was retrieved, false otherwise.
     */
    bool get_info(Info &info, const Key &key, unsigned int occurrence = 1) const;

    bool front(Info &info, Key &key) const;
    bool back(Info &info, Key &key) const;

    /**
     * Searches for the specified element of a given key and occurrence.
     *
     * @param key The key to search for.
     * @param occurrence Specifies which occurrence of the key to consider. Defaults to 1.
     * @return true if the specified element is found, false otherwise.
     */
    bool exists(const Key &key, unsigned int occurrence = 1) const;

    /**
     * Counts the number of occurrences of the given key.
     */
    unsigned int occurrencesOf(const Key &key) const;

    Iterator begin() const;
    Iterator end() const;
};

// operator<<
// sort
// reverse
// swap
// subSequence