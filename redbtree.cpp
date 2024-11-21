//#include <bits/stdc++.h>

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

template<typename K, typename V>
struct RBTreeNode {
    K key;
    V value;
    Color color;
    RBTreeNode<K, V>* left;
    RBTreeNode<K, V>* right;
    RBTreeNode<K, V>* parent;

    RBTreeNode(K k, V val) : key(k), value(val) {
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    bool isLeftChild() const {
        return parent && this == parent->left;
    }
};

template<typename K, typename V>
class RBTree {
public:
    RBTree() {
        root = nullptr;
    }

    void insert(const K& key, const V& value) {
        if (root == nullptr) {
            root = new RBTreeNode<K, V>(key, value);
            root->color = BLACK;
            return;
        }

        RBTreeNode<K, V>* node = root;
        RBTreeNode<K, V>* parent = nullptr;

        while (node != nullptr) {
            parent = node;

            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else {
                node->value = value;
                return;
            }
        }

        node = new RBTreeNode<K, V>(key, value);
        node->parent = parent;

        if (key < parent->key)
            parent->left = node;
        else
            parent->right = node;

        insertFixUp(node);
    }

    void remove(const K& key) {
        RBTreeNode<K, V>* node = findNode(key);

        if (node == nullptr)
            return;

        RBTreeNode<K, V>* child, * parent;
        Color color;

        if (node->left != nullptr && node->right != nullptr) {
            RBTreeNode<K, V>* replace = node->right;
            while (replace->left != nullptr)
                replace = replace->left;

            if (node->parent != nullptr) {
                if (node->isLeftChild())
                    node->parent->left = replace;
                else
                    node->parent->right = replace;
            }
            else
                root = replace;

            child = replace->right;
            parent = replace->parent;
            color = replace->color;

            if (parent == node) {
                parent = replace;
            }
            else {
                if (child != nullptr)
                    child->parent = parent;

                parent->left = child;
                replace->right = node->right;
                node->right->parent = replace;
            }

            replace->parent = node->parent;
            replace->color = node->color;
            replace->left = node->left;
            node->left->parent = replace;

            if (color == BLACK)
                removeFixUp(child, parent);
            delete node;
            return;
        }

        if (node->left != nullptr)
            child = node->left;
        else
            child = node->right;

        parent = node->parent;
        color = node->color;

        if (child != nullptr)
            child->parent = parent;

        if (parent != nullptr) {
            if (node == parent->left)
                parent->left = child;
            else
                parent->right = child;
        }
        else {
            root = child;
        }

        if (color == BLACK)
            removeFixUp(child, parent);

        delete node;
    }

    V& operator[](const K& key) {
        RBTreeNode<K, V>* node = findNode(key);

        if (node != nullptr)
            return node->value;

        V value;
        insert(key, value);
        return findNode(key)->value;
    }

private:
    RBTreeNode<K, V>* root;

    RBTreeNode<K, V>* findNode(const K& key) const {
        RBTreeNode<K, V>* node = root;

        while (node != nullptr) {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else
                return node;
        }

        return nullptr;
    }

    void insertFixUp(RBTreeNode<K, V>* node) {
        RBTreeNode<K, V>* uncle;
        while (node->parent && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;

                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            }
            else {
                uncle = node->parent->parent->left;

                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void removeFixUp(RBTreeNode<K, V>* node, RBTreeNode<K, V>* parent) {
        RBTreeNode<K, V>* sibling;
        while ((!node || node->color == BLACK) && node != root) {
            if (parent->left == node) {
                sibling = parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateLeft(parent);
                    sibling = parent->right;
                }

                if ((!sibling->left || sibling->left->color == BLACK) &&
                    (!sibling->right || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (!sibling->right || sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = parent->right;
                    }

                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->right->color = BLACK;
                    rotateLeft(parent);
                    node = root;
                    break;
                }
            }
            else {
                sibling = parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateRight(parent);
                    sibling = parent->left;
                }

                if ((!sibling->left || sibling->left->color == BLACK) &&
                    (!sibling->right || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (!sibling->left || sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = parent->left;
                    }

                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(parent);
                    node = root;
                    break;
                }
            }
        }

        if (node)
            node->color = BLACK;
    }

    void rotateLeft(RBTreeNode<K, V>* node) {
        RBTreeNode<K, V>* right = node->right;
        node->right = right->left;

        if (right->left != nullptr)
            right->left->parent = node;

        right->parent = node->parent;

        if (node->parent != nullptr) {
            if (node == node->parent->left)
                node->parent->left = right;
            else
                node->parent->right = right;
        }
        else {
            root = right;
        }

        right->left = node;
        node->parent = right;
    }

    void rotateRight(RBTreeNode<K, V>* node) {
        RBTreeNode<K, V>* left = node->left;
        node->left = left->right;

        if (left->right != nullptr)
            left->right->parent = node;

        left->parent = node->parent;

        if (node->parent != nullptr) {
            if (node == node->parent->right)
                node->parent->right = left;
            else
                node->parent->left = left;
        }
        else {
            root = left;
        }

        left->right = node;
        node->parent = left;
    }
};

int main() {
    RBTree<int, int> rbt;
    rbt.insert(10, 123);
    rbt.insert(20, 456);
    rbt.insert(30, 789);

    cout << rbt[10] << '\n' << rbt[20] << '\n';
    cout << rbt[30] << '\n';

    rbt.remove(20);
    cout << rbt[10] << '\n';
    cout << rbt[30] << '\n';

    return 0;
}