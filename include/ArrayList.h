#pragma once
#include "Array.h"
template<typename T>
class ArrayList{
public:
    ArrayList(){
        array = new Array<T>();
    }
    ArrayList(int capacity){
        array=new Array<T>(capacity);
    }
    constexpr int getSize()const{
        return array->getSize();
    }
    constexpr bool isEmpty()const{
        return array->isEmpty();
    }
    constexpr int getCapacity()const{
        return array->getCapacity();
    }
    constexpr T getFirst()const{
        return array->getFirst();
    }
    constexpr T getLast()const{
        return array->getLast();
    }

    ~ArrayList(){
        delete[] array;
        array= nullptr;
    }

private:
    Array<T>*array;
};