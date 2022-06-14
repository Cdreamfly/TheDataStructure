#pragma once

template<typename T>
class Set {
public:
    virtual void add(const T &e) = 0;

    virtual void remove(const T &e) = 0;

    virtual bool contains(const T &e) = 0;

    virtual constexpr bool isEmpty() = 0;

    virtual constexpr int getSize() = 0;

    virtual ~Set() {}
};