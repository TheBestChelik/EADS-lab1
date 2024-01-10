#include <iostream>
#include <iomanip>
#include <functional>
#include <fstream>
#include <chrono>
#pragma once
using namespace std;

template <typename Key, typename Info>
class avl_tree
{
private:
    class Node
    {
    private:
        Node *left;
        Node *right;
        int height;

    public:
        Key key;
        Info info;

        Node(const Key &_key, const Info &_info, Node *left = nullptr, Node *right = nullptr, int height = 1)
            : key(_key), info(_info), left(left), right(right), height(height) {}

        friend class avl_tree;
    };

    Node *root = nullptr;

    int size = 0;

    template <typename Fn>
    void for_each(Node *node, Fn fn)
    {
        if (node == nullptr)
            return;
        for_each(node->left, fn);
        fn(node->key, node->info);
        for_each(node->right, fn);
    }

    void getLargestHelper(Node *node, int &n, vector<pair<Key, Info>> &result)
    {
        if (node == nullptr || n == 0)
        {
            return;
        }

        // Recursively traverse the right subtree first (reverse in-order)
        getLargestHelper(node->right, n, result);

        // Process the current node
        if (n > 0)
        {
            result.push_back(pair<Key, Info>(node->key, node->info));
            n--;
        }

        // Continue with the left subtree if needed
        if (n > 0)
        {
            getLargestHelper(node->left, n, result);
        }
    }

    void getSmallestHelper(Node *node, int &n, vector<pair<Key, Info>> &result)
    {
        if (node == nullptr || n == 0)
        {
            return;
        }

        // Recursively traverse the right subtree first (reverse in-order)
        getSmallestHelper(node->left, n, result);

        // Process the current node
        if (n > 0)
        {
            result.push_back(pair<Key, Info>(node->key, node->info));
            n--;
        }

        // Continue with the left subtree if needed
        if (n > 0)
        {
            getSmallestHelper(node->right, n, result);
        }
    }

    bool isBalancedHelper(typename avl_tree<Key, Info>::Node *node)
    {
        if (node == nullptr)
        {
            return true; // An empty tree is balanced
        }

        // Calculate the balance factor of the current node
        int b_factor = avl_tree<Key, Info>::balanceFactor(node);

        // Check if the balance factor is within the range [-1, 0, 1]
        if (b_factor < -1 || b_factor > 1)
        {
            return false; // The tree is not balanced at this node
        }

        // Recursively check the balance of the left and right subtrees
        return isBalancedHelper(node->left) && isBalancedHelper(node->right);
    }

    void clearHelper(Node *node)
    {
        if (node != nullptr)
        {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
            size--;
        }
    }

    int balanceFactor(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = (node->left != nullptr) ? node->left->height : 0;
        int rightHeight = (node->right != nullptr) ? node->right->height : 0;

        return leftHeight - rightHeight;
    }

    void updateHeight(Node *node)
    {
        if (node != nullptr)
        {
            int leftHeight = (node->left != nullptr) ? node->left->height : 0;
            int rightHeight = (node->right != nullptr) ? node->right->height : 0;

            // Update the height of the current node
            node->height = 1 + std::max(leftHeight, rightHeight);
        }
    }

    Node *copyHelper(const Node *srcNode)
    {
        if (srcNode == nullptr)
        {
            return nullptr;
        }

        // Copy the current node
        Node *newNode = new Node(srcNode->key, srcNode->info);
        newNode->left = copyHelper(srcNode->left);
        newNode->right = copyHelper(srcNode->right);
        newNode->height = srcNode->height;

        return newNode;
    }

    Node *insertHelper(Node *node, const Key &key, const Info &info, function<Info(const Info &oldInfo, const Info &newInfo)> onKeyExists)
    {
        // If the current node is null, create a new node
        if (node == nullptr)
        {
            size++;
            return new Node(key, info);
        }

        // If the key already exists
        if (key == node->key)
        {
            node->info = onKeyExists(node->info, info);
        }
        else if (key < node->key)
        {
            // If the key is less than the current node's key, insert in the left subtree
            node->left = insertHelper(node->left, key, info, onKeyExists);
        }
        else
        {
            // If the key is greater than the current node's key, insert in the right subtree
            node->right = insertHelper(node->right, key, info, onKeyExists);
        }

        return balance(node);
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        x->right = y;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        // Perform left rotation
        Node *y = x->right;
        x->right = y->left;
        y->left = x;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *balance(Node *node)
    {
        updateHeight(node);

        int b_factor = balanceFactor(node);

        if (b_factor > 1)
        {
            // Left-Right case (LR)
            if (balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
            }
            // Left-Left case (LL)
            return rotateRight(node);
        }

        if (b_factor < -1)
        {
            // Right-Left case (RL)
            if (balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);
            }
            // Right-Right case (RR)
            return rotateLeft(node);
        }

        return node;
    }

    Node *findMin(Node *node) const
    {
        if (!node->left)
        {
            return node;
        }
        return findMin(node->left);
    }

    Node *findNode(Node *node, const Key &key) const
    {

        if (node == nullptr || key == node->key)
        {
            return node;
        }

        if (key < node->key)
        {
            return findNode(node->left, key);
        }
        else
        {
            return findNode(node->right, key);
        }
    }

    bool removeHelper(Node *&node, const Key &key)
    {
        if (!node)
        {
            return false; // node not found
        }
        bool deleted = false;
        if (node->key > key)
        {
            deleted = removeHelper(node->left, key);
        }
        else if (node->key < key)
        {
            deleted = removeHelper(node->right, key);
        }
        else
        {
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;

                if (!temp) // no child
                {
                    temp = node;
                    node = nullptr;
                }
                else // one child
                {
                    *node = *temp; // Copy the content of the non-empty child
                }

                delete temp;
            }
            else
            {
                Node *successor = findMin(node->right);
                node->key = successor->key;
                node->info = successor->info;
                removeHelper(node->right, successor->key);
            }

            deleted = true;
        }

        node = balance(node);
        return deleted;
    }

    void printTree(ostream &os, Node *node, int indent) const
    {
        if (node != nullptr)
        {
            // Print right subtree
            printTree(os, node->right, indent + 6);

            // Print current node
            os << std::setw(indent) << ' ';
            os << node->key << ":" << node->info << "\n";

            // Print left subtree
            printTree(os, node->left, indent + 6);
        }
    }

public:
    // Constructor
    avl_tree(){};

    // Copy constructor
    avl_tree(const avl_tree &src)
    {
        *this = src;
    }

    // Destructor
    ~avl_tree()
    {
        clear();
    }

    // Overloaded assignment operator
    avl_tree &operator=(const avl_tree &src)
    {
        if (this != &src)
        {
            clear();
            root = copyHelper(src.root);
            this->size = src.size;
        }

        return *this;
    }

    template <typename Fn>
    void for_each(Fn fn) { for_each(root, fn); }
    vector<pair<Key, Info>> getLargest(int n)
    {
        std::vector<pair<Key, Info>> result;
        getLargestHelper(root, n, result);
        return result;
    }

    vector<pair<Key, Info>> getSmallest(int n)
    {
        std::vector<pair<Key, Info>> result;
        getSmallestHelper(root, n, result);
        return result;
    }

    bool empty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    /**
     * @brief removes all elements from avl tree
     *
     */
    void clear()
    {
        clearHelper(root);
        root = nullptr;
    }

    /**
     * @brief Inserts element to avl tree. If element not exists in the tree it will be inserted. If it exists the action will be defined by onKeyExists.
     *
     * @param key is the key that will be inserted
     * @param info is info that will be inserted
     * @param onKeyExists is function that will be called if key already exists, by default function returns new info
     */
    void insert(
        const Key &key, const Info &info,
        function<Info(const Info &oldInfo, const Info &newInfo)> onKeyExists =
            [](const Info &oldInfo, const Info &newInfo)
        { return newInfo; })
    {
        root = insertHelper(root, key, info, onKeyExists);
    }

    /**
     * @brief removes element from avl tree
     *
     * @param key is the key that will be removed
     * @return true if element was removed
     * @return false if element not exists
     */
    bool remove(const Key &key)
    {
        if (removeHelper(root, key))
        {
            size--;
            return true;
        }
        return false;
    }

    /**
     * @brief searches for element in avl tree
     *
     * @param key is the key that will be searched
     * @return true if element found
     * @return false if element not found
     */
    bool find(const Key &key) const
    {
        return findNode(root, key) != nullptr;
    }

    /**
     * @brief returns info by key
     *
     * @param key is the key that will be searched
     * @return Info& info associated with the key
     */
    Info &operator[](const Key &key)
    {
        Node *node = findNode(root, key);
        if (node == nullptr)
        {
            throw std::runtime_error("Key not found");
        }
        return node->info;
    }

    /**
     * @brief returns info by key
     *
     * @param key is the key that will be searched
     * @return const Info& info associated with the key
     */
    const Info &operator[](const Key &key) const
    {
        Node *node = findNode(root, key);
        if (node == nullptr)
        {
            throw std::runtime_error("Key not found");
        }
        return node->info;
    }

    friend std::ostream &operator<<(std::ostream &os, const avl_tree &tree)
    {
        if (tree.getSize() > 40)
        {
            os << "Tree is too big to print";
            return os;
        }
        tree.printTree(os, tree.root, 0);
        return os;
    }

    // Function designed just for testing
    bool isBalanced()
    {
        return isBalancedHelper(root);
    }
    //
};

// External methods

template <typename Key, typename Info>
std::vector<std::pair<Key, Info>> maxinfo_selector(const avl_tree<Key, Info> &tree, unsigned cnt)
{
    avl_tree<pair<Info, Key>, int> inverted;

    auto copy = tree;

    auto accumulateFn = [&inverted](const Key &key, const Info &info)
    {
        inverted.insert(make_pair(info, key), 1);
    };

    copy.for_each(accumulateFn);

    vector<pair<pair<Info, Key>, int>> largest = inverted.getLargest(cnt);

    vector<pair<Key, Info>> aboba;
    for (auto &pair : largest)
    {
        aboba.push_back(make_pair(pair.first.second, pair.first.first));
    }

    return aboba;
}

avl_tree<string, int> count_words(istream &is)
{
    std::string word;
    avl_tree<string, int> wc;
    while (is >> word)
    {
        wc.insert(word, 1, [](const int &oldValue, const int &newValue)
                  { return oldValue + newValue; });
    }
    return wc;
}
