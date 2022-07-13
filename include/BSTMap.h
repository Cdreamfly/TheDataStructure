#pragma once

#include "Map.h"

template<typename K, typename V>
class BSTNode {
public:
    K key;
    V value;
    BSTNode<K, V> *left, *right;

    BSTNode(K key, V value) : key(key), value(value), left(nullptr), right(nullptr) {}

    BSTNode(BSTNode<K, V> *node) : key(node->key), value(node->value), left(node->left), right(node->right) {}
};

template<typename K, typename V>
class BSTMap : public Map<K, V> {
private:
    BSTNode<K, V> *root;
    int size;
public:
    constexpr int getSize() const {
        return size;
    }

    constexpr bool isEmpty() const {
        return size == 0;
    }

    BSTNode<K, V> *getNode(BSTNode<K, V> *node, K key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->key) {
            return node;
        } else if (key < node->key) {
            return getNode(node->left, key);
        } else {
            return getNode(node->right, key);
        }
    }

    bool contains(K key) {
        return getNode(root, key) != nullptr;
    }

    void add(K key, V value) {
        root = add(root, key, value);
    }

    V *get(K key) {
        BSTNode<K, V> *node = getNode(root, key);
        if(node!= nullptr){
            return &(node->value);
        }
    }

    void set(K key, V value) {
        BSTNode<K, V> *node = getNode(root, key);
        if (node != nullptr) {
            node->value = value;
        }
    }

    V *remove(K key) {
        BSTNode<K, V> *node = getNode(root, key);
        if (node != nullptr) {
            root = remove(root, key);
            return &(node->value);
        }
        return nullptr;
    }

    ~BSTMap() {
        destory(root);
    }

    BSTNode<K, V> *min(BSTNode<K, V> *node) {
        if (node->left == nullptr) {
            return node;
        }
       return min(node->left);
    }

    BSTNode<K, V> *max(BSTNode<K, V> *node) {
        if (node->right == nullptr) {
            return node;
        }
        return min(node->right);
    }

    BSTNode<K, V> *removeMin(BSTNode<K, V> *node) {
        if (node->left == nullptr) {
            BSTNode<K, V> *rightNode = node->right;
            delete node;
            --size;
        }
        node->left = removeMin(node->left);
        return node;
    }

    BSTNode<K, V> *removeMax(BSTNode<K, V> *node) {
        if (node->right == nullptr) {
            BSTNode<K, V> *rightNode = node->left;
            delete node;
            --size;
        }
        node->right = removeMin(node->right);
        return node;
    }

private:
    BSTNode<K, V> *add(BSTNode<K, V> *node, K key, V value) {
        if (node == nullptr) {
            size++;
            return new BSTNode<K, V>(key, value);
        }
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = add(node->left, key, value);
        } else {
            node->right = add(node->right, key, value);
        }
        return node;
    }

    void destory(BSTNode<K, V> *node) {
        if (node != nullptr) {
            destory(node->left);
            destory(node->right);
            delete node;
            --size;
        }
    }

    BSTNode<K, V> *remove(BSTNode<K, V> *node, K key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->key > key) {
            node->left = remove(node->left, key);
            return node;
        } else if (node->key < key) {
            node->right = remove(node->right, key);
            return node;
        } else {
            if (node->left == nullptr) {
                BSTNode<K, V> *rightNode = node->right;
                delete node;
                --size;
                return rightNode;
            }
            if (node->right == nullptr) {
                BSTNode<K, V> *leftNode = node->left;
                delete node;
                --size;
                return leftNode;
            }
            BSTNode<K, V> *succcessor = new BSTNode<K, V>(min(node->right));
            //Node *precursor = new Node(maximum(node->right));
            succcessor->right = removeMin(node->right);
            succcessor->left = node->left;
            //precursor->left = removeMax(node->left);
            //precursor->right = node->right;
            node->left = node->right = nullptr;
            delete node;
            return succcessor;
            //return precursor;
        }
    }
};