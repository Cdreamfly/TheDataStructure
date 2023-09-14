#pragma once

template<typename T>
class Stack {
public:
    [[nodiscard]] constexpr virtual int getSize() const = 0;

    [[nodiscard]] constexpr virtual bool isEmpty() const = 0;

    virtual void push(const T &e) = 0;

    constexpr virtual T pop() = 0;

    virtual T peek() const = 0;

    virtual ~Stack() = default;
};