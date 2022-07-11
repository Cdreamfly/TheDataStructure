#pragma once

template<typename K, typename V>
class Map {
public:
    virtual int getSize() const = 0;

    virtual bool isEmpty() const = 0;

    virtual bool contains(K key) = 0;

    virtual void add(K key, V value) = 0;

    virtual V get(K key) = 0;

    virtual void set(K key, V value) = 0;

    virtual V *remove(K key) = 0;

    virtual ~Map() {}
};