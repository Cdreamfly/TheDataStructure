#pragma once
#include <utility>

template <typename T>
class Vector
{
public:
    Vector() noexcept = default;
    explicit Vector(std::size_t n) : cap_{n}, ptr_{alloc(cap_)}
    {
        for (; len_ < n; ++len_)
        {
            construct(ptr_ + len_); //调用T的默认构造
        }
    }
    Vector(std::size_t n, const T &x) : cap_{n}, ptr_{alloc(cap_)}
    {
        for (; len_ < n; ++len_)
        {
            construct(ptr_ + len_, x); //调用T的拷贝构造
        }
    }
    Vector(const Vector &x) : cap_{x.size()}, ptr_{alloc(cap_)} //拷贝构造
    {
        for (; len_ < x.size(); ++len_)
        {
            construct(ptr_ + len_, x[len_]);
        }
    }
    Vector(Vector &&x) noexcept //移动构造
    {
        cap_ = std::exchange(x.cap_, 0);
        len_ = std::exchange(x.len_, 0);
        ptr_ = std::exchange(x.ptr_, nullptr);
    }
    Vector(std::initializer_list<T> li) : cap_{li.size()}, ptr_{alloc(cap_)} //初始化列表
    {
        for (auto &x : li)
        {
            construct(ptr_ + len_, x);
            ++len_;
        }
    }

    ~Vector() noexcept
    {
        clear();
        dealloc(ptr_);
    }

    void swap(Vector &x) noexcept
    {
        using std::swap; // ADL
        swap(cap_, x.cap_);
        swap(len_, x.len_);
        swap(ptr_, x.ptr_);
    }
    void clear() noexcept
    {
        for (; len_ > 0; --len_)
        {
            destroy(ptr_ + len_ - 1);
        }
    }

    Vector &operator=(const T &x) //拷贝赋值
    {
        if (this != &x)
        {
            Vector{x}.swap(*this);
        }
        return *this;
    }
    Vector &operator=(T &&x) noexcept //移动赋值
    {
        if (this != &x)
        {
            Vector{std::move(x)}.swap(*this);
        }
        return *this;
    }
    Vector &operator=(std::initializer_list<T> li) //初始化列表赋值
    {
        Vector{li}.swap(*this);
        return *this;
    }

    void push_back(const T &x) //拷贝
    {
        emplace_back(x);
    }
    void push_back(T &&x) //移动
    {
        emplace_back(x);
    }
    template <typename... Args>
    void emplace_back(Args &&...args) //直接传递构造函数
    {
        if (len_ == cap_)
        {
            std::size_t new_cap = cap_ ? cap_ * 2 : 1; //等0返回1
            T *new_ptr = alloc(new_cap);
            for (std::size_t new_len; new_len < len_; ++new_len)
            {
                construct(new_ptr + new_len, std::move_if_noexcept(ptr_[new_len]));
            }
            cap_ = new_cap;
            ptr_ = new_ptr;
        }
        construct(ptr_ + len_, std::forward<Args>(args)...);
        ++len_;
    }
    void pop_back() noexcept
    {
        if (len_ < cap_ / 2)
        {
            std::size_t new_cap = cap_ / 2;
            T *new_ptr = alloc(new_cap);
            for (std::size_t new_len = 0; new_len < len_; ++new_len)
            {
                construct(new_ptr + new_len, std::move_if_noexcept(ptr_[new_len]));
            }
            cap_ = new_cap;
            ptr_ = new_ptr;
        }
        destroy(ptr_ + len_ - 1);
        --len_;
    }
    std::size_t size() const noexcept
    {
        return len_;
    }
    std::size_t capacity() const noexcept
    {
        return cap_;
    }
    bool empty() const noexcept
    {
        return len_ == 0;
    }

    T &operator[](std::size_t i)
    {
        return ptr_[i];
    }
    const T &operator[](std::size_t i) const
    {
        return ptr_[i];
    }

    T *begin() noexcept
    {
        return ptr_;
    }
    T *end() noexcept
    {
        return ptr_ + len_;
    }
    const T *begin() const noexcept
    {
        return ptr_;
    }
    const T *end() const noexcept
    {
        return ptr_ + len_;
    }

private:
    T *alloc(std::size_t n) //分配n个大小内存
    {
        return static_cast<T *>(::operator new(sizeof(T) * n));
    }
    void dealloc(T *p) noexcept //释放内存
    {
        ::operator delete(p);
    }
    template <typename... Args>
    void construct(T *p, Args &&...args) //在这块内存上构造T类型对象
    {
        ::new (p) T(std::forward<Args>(args)...);
    }
    void destroy(T *p) noexcept
    {
        p->~T();
    }

private:
    std::size_t cap_{0}; //容量
    std::size_t len_{0}; //元素个数
    T *ptr_{nullptr};
};