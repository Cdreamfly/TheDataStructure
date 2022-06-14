#pragma once

#include "Array.h"

template<typename T>
class MaxHeap {
public:

    class NoParent {
    };

    class Empty {
    };

    MaxHeap() {
        data = new Array<T>();
    }

    ~MaxHeap() {
        delete data;
        data = nullptr;
    }

    MaxHeap(const int capacity) {
        data = new Array<T>(capacity);
    }

    MaxHeap(T arr[], const int n) {
        data = new Array<T>(arr, n);
        for (int i = parent(n - 1); i >= 0; --i) {
            shiftDown(i);
        }
    }

    constexpr int getSize() const {
        return data->getSize();
    }

    constexpr bool isEmpty() const {
        return data->isEmpty();
    }

    // 返回完全二叉树的数组表示中，一个索引所表示的元素的父亲节点的索引
    constexpr int parent(const int index) const {
        if (index == 0) {
            throw new NoParent();
        }
        return (index - 1) / 2;
    }

    void add(const T &e) {
        data->addLast(e);
        shiftUp(data->getSize() - 1);
    }

    T findMax() const {
        if (data->isEmpty()) {
            throw Empty();
        }
        return data->get(0);
    }

    T extractMax() {
        T ret = findMax();
        data->swap(0, data->getSize() - 1);
        data->removeLast();
        shiftDown(0);
        return ret;
    }

    T replace(T e) {
        T ret = findMax();
        data->set(0, e);
        shiftDown(0);
        return ret;
    }

    void print() {
        data->print();
    }

private:

    void shiftDown(int k) {
        while (leftChild(k) < data->getSize()) {
            int j = leftChild(k);
            if (j + 1 < data->getSize() && data->get(j + 1) > data->get(j)) {
                j = rightChild(k);
            }
            if (data->get(k) > data->get(j)) {
                break;
            }
            data->swap(k, j);
            k = j;
        }
    }

    void shiftUp(int index) {
        while (index > 0 && data->get(index) > data->get(parent(index))) {
            data->swap(index, parent(index));
            index = parent(index);
        }
    }

    // 返回完全二叉树的数组表示中，一个索引所表示的元素的左孩子节点的索引
    constexpr int leftChild(const int index) const {
        return (index * 2) + 1;
    }

    // 返回完全二叉树的数组表示中，一个索引所表示的元素的右孩子节点的索引
    constexpr int rightChild(const int index) const {
        return (index * 2) + 2;
    }

private:
    Array<T> *data;
};