#pragma once

template<typename T>
class Queue {
public:
    constexpr virtual int getSize() const = 0;

    constexpr virtual bool isEmpty() const = 0;

    virtual void enqueue(const T &e) = 0;

    virtual T dequeue() = 0;

    constexpr virtual T getFront() const = 0;

    virtual ~Queue() {}
};