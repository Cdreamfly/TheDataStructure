#pragma once

#include <cassert>
#include <iostream>


template<typename T>
class Array {
public:
    //无参构造
    Array() : size(0), capacity(10) {
        data = new T[10];
    }

    //有参构造
    Array(const int Capacity) : size(0), capacity(Capacity) {
        data = new T[capacity];
    }

    //返回当已用容量
    constexpr int getSize() const {
        return size;
    }

    //返回容量
    constexpr int getCapacity() const {
        return capacity;
    }

    //判断是否为空
    constexpr bool isEmpty() const {
        return size == 0;
    }

    //返回索引元素
    constexpr T &get(const int index) const {
        assert(index >= 0 && index <= size);
        return data[index];
    }

    //返回开头元素
    T getFirst() {
        return get(0);
    }

    //返回最后元素
    T getLast() {
        return get(size - 1);
    }

    //[]重载
    const T &operator[](const int index) const {
        assert(index >= 0 && index <= size);
        return data[index];
    }

    //设置索引元素
    void set(const int index, const T &e) {
        assert(index >= 0 && index <= size);
        data[index] = e;
    }

    //在所有元素后添加一个元素
    void addLast(const T &e) {
        add(size, e);
    }

    //在所有元素开头添加一个元素
    void addFirst(const T &e) {
        add(0, e);
    }

    //在index处添加一个元素
    void add(const int index, const T &e) {
        assert(index >= 0 && index <= size);
        if (size == capacity) {
            resize(2 * capacity);
        }
        for (int i = size - 1; i >= index; --i) {
            data[i + 1] = data[i];
        }
        data[index] = e;
        ++size;
    }

    //判断是否有元素e
    constexpr bool contains(const T &e) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == e) {
                return true;
            }
        }
        return false;
    }

    //删除第一个元素
    T removeFirst() {
        return remove(0);
    }

    //删除最后一个元素
    T removeLast() {
        return remove(size - 1);
    }

    //删除数组中元素e
    int removeElement(const T &e) {
        int index = find(e);
        if (index != -1) {
            return remove(index);
        }
        return -1;
    }

    //删除index位置的元素
    T remove(const int index) {
        assert(index >= 0 && index <= size);
        int ret = data[index];
        for (int i = index + 1; i < size; ++i) {
            data[i - 1] = data[i];
        }
        --size;
        data[size] = 0;
        if (size == capacity / 2 && capacity / 2 != 0) {
            resize(capacity / 2);     //缩减容量
        }
        return ret;
    }

    //查找元素e
    constexpr int find(const T &e) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == e) {
                return i;
            }
        }
        return -1;
    }

    ~Array() {
        delete[] data;
        data = nullptr;
    }

    void print() {
        std::cout << "Array: size = " << size << ", capacity = " << getCapacity() << std::endl;
        std::cout << "[";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i != size - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]";
        std::cout << std::endl;
    }

private:
    //自动扩容
    void resize(const int newCapacity) {
        T *newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        newData = nullptr;
        delete[] newData;
    }

    T *data;        //数据
    int size;       //有效数据数
    int capacity;   //容量
};