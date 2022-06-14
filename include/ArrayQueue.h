#pragma once

#include "Array.h"
#include "Queue.h"

template<typename T>
class ArrayQueue : public Queue<T> {
public:
    ArrayQueue() {
        array = new Array<T>();
    }

    ArrayQueue(const int capacity) {
        array = new Array<T>(capacity);
    }

    constexpr int getSize() const {
        return array->getSize();
    }

    constexpr int getCapacity() const {
        return array->getCapacity();
    }

    constexpr bool isEmpty() const {
        return array->isEmpty();
    }

    void enqueue(const T &e) {
        array->addLast(e);
    }

    T dequeue() {
        return array->removeFirst();    //时间复杂度:O(n)
    }

    constexpr T getFront() const {
        return array->getFirst();
    }

    ~ArrayQueue() {
        delete[] array;
        array = nullptr;
    }

    void print() {
        std::cout << "ArrayQueue: size = " << array->getSize() << ", capacity = " << array->getCapacity() << std::endl;
        std::cout << "front ";
        array->print();
        std::cout << " tail" << std::endl;
    }

private:
    Array<T> *array;
};