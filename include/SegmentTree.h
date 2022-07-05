//
// Created by Cmf on 2022/7/5.
//
#pragma once

#include <cassert>
#include <functional>

template<typename T>
class SegmentTree {
public:
    SegmentTree() noexcept = default;

    explicit SegmentTree(T *arr, int n, std::function<T(T, T)> func) : data(new T[n]), tree(new T[4 * n]),
                                                                       size(n), function(func) {
        for (int i = 0; i < n; ++i) {
            data[i] = arr[i];
        }
        //构建线段树 根索引为0，左边界为0，有边界为 size-1
        buildSegmentTree(0, 0, size - 1);
    }

    ~SegmentTree() noexcept {

    }

    constexpr int getSize() const noexcept {
        return size;
    }

    T get(const int index) const {
        assert(index >= 0 && index < size);
        return data[index];
    }

    void print() {
        std::cout << "[";
        for (int i = 0; i < size * 4; ++i) {
            if (tree[i] != NULL) {
                std::cout << tree[i];
            } else {
                std::cout << "0";
            }
            if (i != size * 4 - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

private:
    void buildSegmentTree(int treeIndex, int left, int right) {
        //如果左右相等就说明递归到底，
        if (left == right) {
            tree[treeIndex] = data[left];
            return;
        }
        int leftChildIndex = leftChild(treeIndex);
        int rightChildIndex = rightChild(treeIndex);
        int mid = left + (right - left) / 2;
        //递归左右孩子
        buildSegmentTree(leftChildIndex, left, mid);
        buildSegmentTree(rightChildIndex, mid + 1, right);
        //线段存储信息根据业务写相应的代码，以求和为例，
        tree[treeIndex] = function(tree[leftChildIndex], tree[rightChildIndex]);
    }

    constexpr int leftChild(const int index) const noexcept {
        return index * 2;
    }

    constexpr int rightChild(const int index) const noexcept {
        return index * 2 + 1;
    }

private:
    std::function<T(T, T)> function;
    T *tree;
    T *data;
    int size;
};
