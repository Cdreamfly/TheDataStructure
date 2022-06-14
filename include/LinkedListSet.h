#pragma once
#include "LinkedList.h"
#include "Set.h"

template<typename T>
class LinkedListSet : public Set<T> {
public:
    LinkedListSet() {
        list = new LinkedList<T>();
    }

    void add(const T &e) {
        if(!list->contains(e)){
            list->addFirst(e);
        }
    }

    void remove(const T &e) {
        list->removeElement(e);
    }

    bool contains(const T &e) {
        return list->contains(e);
    }

    constexpr bool isEmpty() {
        return list->isEmpty();
    }

    constexpr int getSize() {
        return list->getSize();
    }

    ~LinkedListSet() {
        delete list;
        list= nullptr;
    }

private:
    LinkedList<T>*list;
};