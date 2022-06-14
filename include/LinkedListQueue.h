#pragma once
#include "Queue.h"
#include <iostream>

template<typename T>
class Node {
public:
    T e;
    Node *next;

    Node() : e(0), next(nullptr) {

    }

    Node(const T &E) : e(E), next(nullptr) {

    }

    Node(const T &E, Node<T> *Next) : e(E), next(Next) {

    }
};

template<typename T>
class LinkedListQueue : public Queue<T> {
public:
    LinkedListQueue() : head(nullptr), tail(nullptr), size(0) {

    }

    constexpr int getSize() const {
        return size;
    }

    constexpr bool isEmpty() const {
        return size == 0;
    }

    void enqueue(const T &e) {
        if (tail == nullptr) {
            tail = new Node<T>(e);
            head = tail;
        } else {
            tail->next = new Node<T>(e);
            tail = tail->next;
        }
        ++size;
    }

    T dequeue() {
        assert(!isEmpty());
        Node<T>*retNode=head;
        head=head->next;
        retNode->next= nullptr;
        if(head== nullptr){
            tail= nullptr;
        }
        --size;
        T temp=retNode->e;
        delete retNode;
        retNode= nullptr;
        return temp;
    }

    constexpr T getFront() const {
        assert(!isEmpty());
        return head->e;
    }
    ~LinkedListQueue(){
        Node<T>*temp;
        while(head!= nullptr){
            temp=head->next;
            delete head;
            head=temp;
        }
    }
    void print() {
        Node<T> *prev = head;
        std::cout << "LinkListQueue: size = " << size << std::endl;
        std::cout << "front ";
        std::cout << "[";
        while (prev != nullptr) {
            std::cout << prev->e;
            if (prev->next != nullptr) {
                std::cout << ", ";
            }
            prev = prev->next;
        }
        std::cout << "] tail" << std::endl;
    }
private:
    Node<T> *head, *tail;
    int size;
};