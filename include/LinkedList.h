#pragma once
#include <assert.h>
#include <iostream>

template<typename T>
class ListNode {
public:
    T e;
    ListNode<T> *next;

    ListNode() : next(nullptr) {}

    ListNode(const T &E) : e(E), next(nullptr) {}

    ListNode(const T &E, ListNode<T> *Next) : e(E), next(Next) {}
};

template<typename T>
class LinkedList {
public:
    LinkedList() : size(0) {
        dummyHead = new ListNode<T>();
    }

    constexpr int getSize() const {
        return size;
    }

    constexpr bool isEmpty() const {
        return size == 0;
    }

    void add(const int index, const T &e) {
        assert(index >= 0 && index <= size);
        ListNode<T> *prev = dummyHead;
        for (int i = 0; i < index; ++i) {
            prev = prev->next;
        }
        prev->next = new ListNode<T>(e, prev->next);
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
        ListNode<T> *cur = dummyHead->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        cur->e = e;
    }

    void setFirst(const T &e) {
        set(0, e);
    }

    void setLast(const T &e) {
        set(size - 1, e);
    }

    bool contains(const T &e) const {
        ListNode<T> *cur = dummyHead->next;
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
        ListNode<T> *cur = dummyHead->next;
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
        ListNode<T> *prev = dummyHead;
        for (int i = 0; i < index; ++i) {
	        prev = prev->next;
        }
        ListNode<T> *retListNode = prev->next;
	    prev->next = retListNode->next;
        retListNode->next = nullptr;
        --size;
        T temp = retListNode->e;
        delete retListNode;
        retListNode = nullptr;
        return temp;
    }

    T removeFirst() {
        remove(0);
    }

    T removeLast() {
        remove(size - 1);
    }

    void removeElement(const T &e) {
        ListNode<T> *prev = dummyHead;
        while (prev->next != nullptr) {
            if (prev->next->e == e) {
                break;
            }
            prev = prev->next;
        }

        if (prev->next != nullptr) {
            ListNode<T> *delListNode = prev->next;
            prev->next = delListNode->next;
            delListNode->next = nullptr;
            delete delListNode;
            delListNode = nullptr;
            --size;
        }
    }

    ~LinkedList() {
        ListNode<T> *cur = dummyHead->next;
        ListNode<T> *temp;
        while (cur != nullptr) {
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        dummyHead->next = nullptr;
        delete dummyHead;
        dummyHead = nullptr;
    }

    void print() {
        ListNode<T> *prev = dummyHead;
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
    ListNode<T> *dummyHead;
    int size;
};