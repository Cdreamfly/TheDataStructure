#pragma once
#include <assert.h>
#include <iostream>

template<typename T>
class Node {
public:
    T e;
    Node *prev;
    Node *next;

    Node() : e(0), prev(nullptr), next(nullptr) {

    }

    Node(const T &E) : e(E), prev(nullptr), next(nullptr) {

    }

    Node(const T &E, Node<T> *Prev, Node<T> *Next) : e(E), prev(Prev), next(Next) {

    }
};

template<typename T>
class DoubleLinkedListHT {
public:
    DoubleLinkedListHT() : size(0) {
        head = new Node<T>(0, nullptr, head);
        tail = new Node<T>(0, tail, nullptr);
    }

    constexpr int getSize() const {
        return size;
    }

    constexpr bool isEmpty() const {
        return size == 0;
    }

    void add(const int index, const T &e) {
        assert(index >= 0 && index <= size);
        Node<T> *prevNode = head;
        for (int i = 0; i < index; ++i) {
            prevNode = prevNode->next;
        }
        prevNode->next = new Node<T>(e, prevNode, prevNode->next);
        prevNode->next->next->prev = prevNode->next;
        ++size;
    }

    void addFirst(const T &e) {
        head->next = new Node<T>(e, head, head->next);
        head->next->next->prev = head->next;
        ++size;
    }

    void addLast(const T &e) {
        tail->prev = new Node<T>(e, tail->prev, tail);
        tail->prev->prev->next = tail->prev;
        ++size;
    }

    void set(const int index, const T &e) {
        assert(index >= 0 && index < size);
        Node<T> *cur = head->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        cur->e = e;
    }

    void setFirst(const T &e) {
        head->next->e = e;
    }

    void setLast(const T &e) {
        tail->prev->e = e;
    }

    bool contains(const T &e) const {
        Node<T> *cur = head->next;
        while (cur != nullptr) {
            if (cur->e == e) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    T get(const int index) const {
        assert(index >= 0 && index < size);
        Node<T> *cur = head->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->e;
    }

    T getFirst() const {
        return head->next->e;
    }

    T getLast() const {
        return tail->prev->e;
    }

    T remove(int index) {
        assert(index >= 0 && index < size);
        Node<T> *prevNode = head;
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
        Node<T> *retNode = tail->prev;
        T temp = retNode->e;
        tail->prev = retNode->prev;
        retNode->prev->next = tail;
        retNode->next = nullptr;
        retNode->prev = nullptr;
        delete retNode;
        retNode = nullptr;
        --size;
        return temp;
    }

    ~DoubleLinkedListHT() {
        Node<T> *cur = head->next;
        Node<T> *temp;
        while (cur != nullptr) {
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        head->next = nullptr;
        head->prev = nullptr;
        tail->prev = nullptr;
        tail->next = nullptr;
        delete head;
        head = nullptr;
        delete tail;
        tail = nullptr;
    }

    void print() {
        Node<T> *prevNode = head;
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
    Node<T> *head, *tail;
    int size;
};