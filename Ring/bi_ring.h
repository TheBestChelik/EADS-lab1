template <typename Key, typename Info>
class bi_ring
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

        Node(const Key &_key, const Info &_info, Node *_next, Node *_prev)
            : key(_key), info(_info), next(_next), prev(_prev) {}

        friend class bi_ring;
    };

public:
    template <typename Key, typename Info>
    class iterator
    {
        friend class bi_ring<Key, Info>;

    protected:
        Node *current;

    public:
        iterator(Node *ptr = nullptr);
        iterator(const iterator &other);

        ~iterator();

        iterator &operator++();

        iterator operator++(int);

        iterator &operator--();

        iterator operator--(int);

        bool operator==(const iterator &other) const;

        bool operator!=(const iterator &other) const;
    };

    // Const Iterator class
    template <typename Key, typename Info>
    class const_iterator : public iterator<Key, Info>
    {
        friend class bi_ring<Key, Info>;

    public:
        using typename iterator<Key, Info>::iterator;

        /**
         *
         * @return const Key& on which iterator is pointing
         */
        const Key &key() const;

        /**
         *
         * @return const Info& on which iterator is pointing
         */
        const Info &info() const;
    };

    // Modifying Iterator class
    template <typename Key, typename Info>
    class modifying_iterator : public iterator<Key, Info>
    {
        friend class bi_ring<Key, Info>;

    public:
        using typename iterator<Key, Info>::iterator;

        /**
         *
         * @return Key& on which iterator is pointing
         */
        Key &key() const;

        /**
         *
         * @return Info& on which iterator is pointing
         */
        Info &info() const;
    };

    bi_ring();
    bi_ring(const bi_ring &src);
    ~bi_ring();
    bi_ring &operator=(const bi_ring &src);

    /**
     * @brief Get the Length of ring
     *
     * @return int len of ring
     */
    int getLength() const;

    /**
     * Checks if ring is empty
     *
     * @return true if ring is empty
     * @return false if ring is not empty
     */
    bool isEmpty() const;

    /**
     * Inserts a new element with the provided key and info after the specified node
     * on which iterator os pointing at.
     *
     * @param position Iterator pointing on node after which the new node has to be inserted
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @return iterator pointing on inserted node
     */
    iterator insert_after(iterator position, const Key &key, const Info &info);

    /**
     * Inserts a new element with the provided key and info before the specified node
     * on which iterator os pointing at.
     *
     * @param position Iterator pointing on node after which the new node has to be inserted
     * @param key The key of the new element to insert.
     * @param info The info of the new element to insert.
     * @return iterator pointing on inserted node
     */
    iterator insert_before(iterator position, const Key &key, const Info &info);

    /**
     * Removes the specified element.
     *
     * @param position The key of the element to remove.
     * @return true if an element was successfully removed, false otherwise.
     */
    iterator erase(iterator position);

    /**
     * @brief clears the ring
     *
     */
    void clear();

    /**
     * Searches for the specified element of a given key.
     *
     * @param [out] it is iterator pointing on found element
     * @param key The key to search for.
     * @param search_from iterator pointing on element from which start searching
     * @param search_till iterator pointing on element until which element to search
     * @return true if element found
     * @return false if element not found
     */
    bool find(iterator &it, const Key &key, iterator &search_from, iterator &search_till);

    /**
     * @brief number of occurrences of key
     *
     * @param key is key which occurrences we count
     * @return unsigned int number of occurrences of key
     */
    unsigned int occurrencesOf(const Key &key) const;

    // why do we need it, if we have insert and erase???
    iterator push_front(const Key &key, const Info &info);
    iterator push_back(const Key &key, const Info &info);
    iterator pop_front();
    iterator pop_back();
    //
};
