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

    explicit SegmentTree(const T *const arr, const int n, std::function<T(T, T)> func) : data(new T[n]),
                                                                                         tree(new T[4 * n]),
                                                                                         size(n),
                                                                                         function(func) {
        for (int i = 0; i < n; ++i) {
            data[i] = arr[i];
        }
        //构建线段树 根索引为0，左边界为0，有边界为 size-1
        buildSegmentTree(0, 0, size - 1);
    }

    ~SegmentTree() noexcept {
        delete[] data;
        data = nullptr;
        delete[] tree;
        tree = nullptr;
    }

    constexpr int getSize() const noexcept {
        return size;
    }

    T get(const int index) const {
        assert(index >= 0 && index < size);
        return data[index];
    }

    T query(const int queryL, const int queryR) {
        assert(queryL >= 0 && queryL < size && queryR >= 0 && queryR < size && queryL <= queryR);
        return query(0, 0, size - 1, queryL, queryR);
    }

    void set(const int index, const T &e) {
        assert(index >= 0 && index < size);
        data[index] = e;
        set(0, 0, size - 1, index, e);
    }

    void print() const {
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

    void set(const int treeIndex, const int l, const int r, const int index, const T &e) {
        //都叶子了，一定是它了，更新它
        if (l == r) {
            tree[treeIndex] = e;
            return;
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        //要找的索引大于中间值，一定在右边
        if (index >= mid + 1) {
            set(rightTreeIndex, mid + 1, r, index, e);
        } else if (index <= mid) {  //否则在左边
            set(leftTreeIndex, l, mid, index, e);
        }
        //更新...
        tree[treeIndex] = function(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    //在以treeIndex为根的线段树[l...r]的范围里，搜索区间[queryL,queryR]的值
    int query(const int treeIndex, const int l, const int r, const int queryL, const int queryR) {
        //如果左右相同就找到了
        if (l == queryL && r == queryR) {
            return tree[treeIndex];
        }
        int mid = l + (r - l) / 2;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        //如果查找的范围左边界大于中间
        if (mid + 1 <= queryL) {
            //那么就不用查找左边
            return query(rightTreeIndex, mid + 1, r, queryL, queryR);
            //如果查找的范围右边小于中间
        } else if (mid >= queryR) {
            //那么就不用查找右边
            return query(leftTreeIndex, l, mid, queryL, queryR);
        }
        //如果查找的范围占用两个区间
        T leftResult = query(leftTreeIndex, l, mid, queryL, mid);
        T rightResult = query(rightTreeIndex, mid + 1, r, mid + 1, queryR);
        return function(leftResult, rightResult);
    }

    void buildSegmentTree(const int treeIndex, const int left, const int right) {
        //如果左右相等就说明递归到底
        if (left == right) {
            tree[treeIndex] = data[left];
            return;
        }
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        int mid = left + (right - left) / 2;
        //递归左右孩子根为左右孩子索引，左右边界以中间为界
        buildSegmentTree(leftTreeIndex, left, mid);
        buildSegmentTree(rightTreeIndex, mid + 1, right);
        //线段存储信息根据业务写相应的代码，以求和为例，
        tree[treeIndex] = function(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    constexpr int leftChild(const int index) const noexcept {
        return index * 2 + 1;
    }

    constexpr int rightChild(const int index) const noexcept {
        return index * 2 + 2;
    }

private:
    std::function<T(T, T)> function;
    T *tree;
    T *data;
    int size;
};
