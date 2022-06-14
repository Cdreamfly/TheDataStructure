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
class DoubleLoopLinkList {
public:
    DoubleLoopLinkList() : size(0) {
        dummyHead = new Node<T>(0, dummyHead, dummyHead);
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
        prevNode->next->next->prev = prevNode->prev;
        ++size;
    }

    void addFirst(const T &e) {
        dummyHead->next = new Node<T>(e, dummyHead, dummyHead->next);
        dummyHead->next->next->prev = dummyHead->next;
        ++size;
    }

    void addLast(const T &e) {
        dummyHead->prev = new Node<T>(e, dummyHead->prev, dummyHead);
        dummyHead->prev->prev->next = dummyHead->prev;
        ++size;
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
        assert(!isEmpty());
        dummyHead->next->e = e;
    }

    void setLast(const T &e) {
        assert(!isEmpty());
        dummyHead->prev->e = e;
    }

    bool contains(const T &e) const {
        Node<T> *cur = dummyHead->next;
        while (cur != dummyHead) {
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
        assert(!isEmpty());
        return dummyHead->next->e;
    }

    T getLast() const {
        assert(!isEmpty());
        return dummyHead->prev->e;
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
        remove(0);
    }

    T removeLast() {
        Node<T> *retNode = dummyHead->prev;
        T temp = retNode->e;
        dummyHead->prev = retNode->prev;
        retNode->prev->next = dummyHead;
        retNode->next = nullptr;
        retNode->prev = nullptr;
        delete retNode;
        retNode = nullptr;
        --size;
        return temp;
    }

    ~DoubleLoopLinkList() {
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
        Node<T> *prev = dummyHead;
        std::cout << "LinkedList: size = " << size << std::endl;
        std::cout << "[";
        for (int i = 0; i < size; ++i) {
            prev = prev->next;
            std::cout << prev->e;
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

#endif //LINKEDLIST_DOUBLELOOPLINKLIST_H
