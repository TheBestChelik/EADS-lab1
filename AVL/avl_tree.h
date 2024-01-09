#include <iostream>
#include <iomanip>
#include <functional>
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

    Node *findMax(Node *node);
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
        // root = copyHelper(src.root);
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
        { // Check for self-assignment
            // Clear the existing content
            clear();
            // Copy the content from the source tree
            root = copyHelper(src.root);
            this->size = src.size;
        }

        return *this;
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
    } // tree[aboba] = 1

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
        tree.printTree(os, tree.root, 0);
        return os;
    }

    // Function designed for testing
    bool isBalanced()
    {
        return isBalancedHelper(root);
    }
    //
};
