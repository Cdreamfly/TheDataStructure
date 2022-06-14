#pragma once

#include "BST.h"
#include "Set.h"

template<typename T>
class BSTSet : public Set<T> {
public:

    BSTSet() {
        bst = new BST<T>();
    }

    void add(const T &e) {
        bst->add(e);
    }

    void remove(const T &e) {
        bst->RRemove(e);
    }

    bool contains(const T &e) {
        return bst->contains(e);
    }

    constexpr bool isEmpty() {
        return bst->isEmpty();
    }

    constexpr int getSize() {
        return bst->getSize();
    }

    ~BSTSet() {
        delete bst;
        bst = nullptr;
    }

private:
    BST<T> *bst;
};