#pragma once

#include <assert.h>
#include "Queue.h"

template<typename T>
class LoopQueue : public Queue<T> {
public:
    LoopQueue() : front(0), tail(0), capacity(10) {
        data = new T(10);
    }

    LoopQueue(const int Capacity) : front(0), tail(0), capacity(Capacity) {
        data = new T(Capacity);
    }

    constexpr int getSize() const {
        return (tail + capacity - front) % capacity;;
    }

    constexpr int getCapacity() const {
        return capacity;
    }

    constexpr bool isEmpty() const {
        return front == tail;
    }

    void enqueue(const T &e) {
        if ((tail + 1) % capacity == front) {
            resize(capacity * 2); //如果队列为满则扩容
        }
        data[tail] = e; //入队元素放队尾
        tail = (tail + 1) % capacity;
    }

    T dequeue() {
        assert(!isEmpty());
        T ret = data[front]; //暂存队首元素
        front = (front + 1) % capacity; //front+1
        if (getSize() == capacity / 4 && capacity / 2 != 0) {//如果元素个数只有容量的1/4且不为空
            resize(capacity / 2); //缩减为原本1/2
        }
        return ret;
    }

    constexpr T getFront() const {
        assert(!isEmpty());
        return data[front];
    }

    void print() {
        std::cout << "LoopQueue: size = " << getSize() << ", capacity = " << capacity << std::endl;
        std::cout << "front [";
        for (int i = front; i != tail; i = (i + 1) % capacity) {
            std::cout << data[i];
            if ((i + 1) % capacity != tail) {
                std::cout << ", ";
            }
        }
        std::cout << "] tail" << std::endl;
    }

    ~LoopQueue() {
        delete[] data;
        data = nullptr;
    }

private:
    void resize(const int newCapacity) {
        // 将数组空间的容量变成newCapacity大小
        T *newData = new T[newCapacity + 1];
        for (int i = 0; i < getSize(); ++i) {
            newData[i] = data[(i + front) % capacity];  //把元素放入新数组空间
        }
        data = newData; //数组空间指向新数组空间
        tail = getSize();   //更新
        front = 0;
        capacity = newCapacity;
        newData = nullptr;//新数组指向空
        delete[]newData;//删除新数组
    }

private:
    T *data;
    int front, tail;
    int capacity;
};