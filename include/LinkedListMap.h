#pragma once

#include "LinkedList.h"
#include "Map.h"

template<typename K, typename V>
class MapNode {
public:
    K key;
    V value;
    MapNode<K, V> *next;

    MapNode() : next(nullptr) {}

    MapNode(const K &k) : key(k), next(nullptr) {}

    MapNode(const K &k, const V &v, MapNode<K, V> *Next) : key(k), value(v), next(Next) {}
};


template<typename K, typename V>
class LinkedListMap : public Map<K, V> {
public:
    LinkedListMap() : size(0) {
        dummyHead = new MapNode<K, V>();
    }

    void add(const K &k, const V &v) {
        MapNode<K, V> *node = getNode(k);
        if (node == nullptr) {
            dummyHead->next = new MapNode(k, v, dummyHead->next);
            ++size;
        } else {
            node->value = v;
        }
    }

    V get(const K &k) {
        MapNode<K, V> *node = getNode(k);
        if(node!= nullptr) {
            return node->value;
        }
    }

    V remove(const K &k) {
        assert(contains(k));
        MapNode<K, V> *prev = dummyHead;
        while (prev->next != nullptr) {
            if (prev->next->key == k) {
                break;
            }
            prev = prev->next;
        }
        if (prev->next != nullptr) {
            MapNode<K, V> *delNode = prev->next;
            V v = delNode->value;
            prev->next = delNode->next;
            delNode->next = nullptr;
            delete delNode;
            --size;
            return v;
        }
    }

    bool contains(const K &k) {
        return getNode(k) != nullptr;
    }

    void set(const K &k, const V &v) {
        MapNode<K, V> *node = getNode(k);
        if (node == nullptr) {
            add(k, v);
        } else {
            node->value = v;
        };

    }

    constexpr int getSize() {
        return size;
    }

    constexpr bool isEmpty() {
        return size == 0;
    }

private:
    MapNode<K, V> *getNode(const K &k) {
        MapNode<K, V> *cur = dummyHead->next;
        while (cur != nullptr) {
            if (cur->key == k) {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }

private:
    MapNode<K, V> *dummyHead;
    int size;
};