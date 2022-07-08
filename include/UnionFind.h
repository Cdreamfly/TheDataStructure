#pragma once

#include "UF.h"
#include<cassert>

class UnionFind : public UF {
public:
    UnionFind(int cap) : size(cap) {
        parent = new int[size];
        rank = new int[size];
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind() noexcept {
        delete[] parent;
        parent = nullptr;
    }

    const int getSize() const noexcept override {
        return size;
    }

    //查询元素p和q是否在一个集合
    bool isConnected(int p, int q) override {
        return find(p) == find(q);
    }

    //合并元素p和q的集合
    void unionElements(int p, int q) override {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot == qRoot) {
            return;
        }
        //就把其中一个的根节点挂到另一个的根上
        if (rank[pRoot] < rank[qRoot]) {
            parent[pRoot] = qRoot;  //高度小的根节点指向高度大的根节点，从而减少树的高度，防止退化
        } else if (rank[qRoot] < rank[pRoot]) {
            parent[qRoot] = pRoot;
        } else {
            parent[qRoot] = pRoot;
            ++rank[pRoot];
        }
    }

private:
    //查找元素p对应的集合编号，O(h)复杂度, h为树的高度
    //根节点就是集合编号，且根节点指向自己，索引 p == parent[p]
    int find(int p) {
        assert(p >= 0 && p < size);
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];  //路径压缩，让p这个节点指向它父亲的父亲
            p = parent[p];
        }
        return p;
    }
    //递归版路径压缩，让集合中所有节点指向根节点
    int recFind(int p) {
        assert(p >= 0 && p < size);
        if (p != parent[p]) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

private:
    int *parent;
    int *rank;
    int size;
};