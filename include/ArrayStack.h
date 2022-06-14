#pragma once

#include "Stack.h"
#include "Array.h"

template<typename T>
class ArrayStack : public Stack<T> {
public:
    ArrayStack(const int capacity) {
        array = new Array<T>(capacity);
    }

    ArrayStack() {
        array = new Array<T>();
    }

    //返回大小
    constexpr int getSize()const{
        return array->getSize();
    }

    //判空
    constexpr bool isEmpty()const {
        return array->isEmpty();
    }

    //返回栈容积
    constexpr int getCapacity() const{
        return array->getCapacity();
    }

    //入栈
    void push(const T& e) {
        array->addLast(e);
    }

    //出栈
    T pop() {
        return array->removeLast();
    }

    //返回栈顶元素
    constexpr T peek()const {
        return array->getLast();
    }

    ~ArrayStack() {
        delete[] array;
        array = nullptr;
    }

    //打印
    void print() {
        std::cout << "ArrayStack: size = " << array->getSize() << ", capacity = " << array->getCapacity() << std::endl;
        std::cout << "bottom ";
        array->print();
        std::cout << " top" << std::endl;
    }

private:
    Array<T> *array;
};