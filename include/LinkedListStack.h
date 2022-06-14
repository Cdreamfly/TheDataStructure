#pragma once
#include "Stack.h"
#include "LinkedList.h"

template<typename T>
class LinkedListStack : public Stack<T> {
public:
    LinkedListStack() {
        list = new LinkedList<T>();
    }

    constexpr int getSize() const {
        return list->getSize();
    }

    constexpr bool isEmpty() const {
        return list->isEmpty();
    }

    void push(const T &e) {
        list->addFirst(e);
    }

    constexpr T pop() {
        return list->removeFirst();
    }

    T peek() const {
        return list->getFirst();
    }

    ~LinkedListStack() {
        delete[] list;
        list = nullptr;
    }

    void print() {
        std::cout << "Stack: size = " << list->getSize() << std::endl;
        std::cout << "bottom ";
        list->toPrint();
        std::cout << " top" << std::endl;
    }

private:
    LinkedList<T> *list;
};