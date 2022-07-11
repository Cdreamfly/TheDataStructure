#pragma once

#include "Set.h"
#include "AVLTree.h"

template<class T>
class AVLSet : public Set<T> {
private:
    AVLTree<T, T> *avlTree;

public:
    AVLSet() {
        avlTree = new AVLTree<T, T>();
    }

    ~AVLSet(){
        delete avlTree;
        avlTree = nullptr;
    }

    int getSize() {
        return avlTree->getSize();
    }

    constexpr bool isEmpty() {
        return avlTree->isEmpty();
    }

    void add(const T &e) {
        avlTree->add(e, nullptr);
    }

    bool contains(const T &e) {
        return avlTree->contains(e);
    }

    void remove(const T &e) {
        avlTree->remove(e);
    }
};
