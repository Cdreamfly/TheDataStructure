#pragma once
#include <assert.h>
#include <iostream>

template<typename T>
class Node {
public:
    T e;
    Node *prev;
    Node *next;

    Node() : prev(nullptr), next(nullptr) {}

    Node(const T &E) : e(E), prev(nullptr), next(nullptr) {}

    Node(const T &E, Node<T> *Prev, Node<T> *Next) : e(E), prev(Prev), next(Next) {}
};

template<typename T>
class DoubleLinkedList {
public:
    DoubleLinkedList() : size(0) {
        dummyHead = new Node<T>(0, nullptr, dummyHead);
    }

    constexpr int getSize() const {
        return size;
    }

    constexpr bool isEmpty() const {
        return size == 0;
    }

    void add(const int index, const T &e) {
        assert(index >= 0 && index <= size);
        Node<T> *prevNode = dummyHead;
        for (int i = 0; i < index; ++i) {
            prevNode = prevNode->next;
        }
        prevNode->next = new Node<T>(e, prevNode, prevNode->next);
        prevNode->next->next->prev = prevNode->next;
        ++size;
    }

    void addFirst(const T &e) {
        add(0, e);
    }

    void addLast(const T &e) {
        add(size, e);
    }

    void set(const int index, const T &e) {
        assert(index >= 0 && index < size);
        Node<T> *cur = dummyHead->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        cur->e = e;
    }

    void setFirst(const T &e) {
        set(0, e);
    }

    void setLast(const T &e) {
        set(size, e);
    }

    bool contains(const T &e) const {
        Node<T> *cur = dummyHead->next;
        while (cur != nullptr) {
            if (cur->e = e) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    T get(const int index) const {
        assert(index >= 0 && index < size);
        Node<T> *cur = dummyHead->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->e;
    }

    T getFirst() const {
        return get(0);
    }

    T getLast() const {
        return get(size - 1);
    }

    T remove(int index) {
        assert(index >= 0 && index < size);
        Node<T> *prevNode = dummyHead;
        for (int i = 0; i < index; ++i) {
            prevNode = prevNode->next;
        }
        Node<T> *retNode = prevNode->next;
        prevNode->next = retNode->next;
        retNode->next->prev = retNode->prev;
        retNode->next = nullptr;
        retNode->prev = nullptr;
        --size;
        T temp = retNode->e;
        delete retNode;
        retNode = nullptr;
        return temp;
    }

    T removeFirst() {
        return remove(0);
    }

    T removeLast() {
        return remove(size - 1);
    }

    ~DoubleLinkedList() {
        Node<T> *cur = dummyHead->next;
        Node<T> *temp;
        while (cur != nullptr) {
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        dummyHead->next = nullptr;
        dummyHead->prev = nullptr;
        delete dummyHead;
        dummyHead = nullptr;
    }

    void print() {
        Node<T> *prevNode = dummyHead;
        std::cout << "LinkedList: size = " << size << std::endl;
        std::cout << "[";
        for (int i = 0; i < size; ++i) {
            prevNode = prevNode->next;
            std::cout << prevNode->e;
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

private:
    Node<T> *dummyHead;
    int size;
};