#pragma once
#include <cstddef>
template <typename T>
class shared_ptr
{
private:
    T *ptr_;
    size_t *ref_count_;
    void release()
    {
        if (ref_count_)
        {
            (*ref_count_)--;
            if (*ref_count_ == 0)
            {
                delete ptr_;
                delete ref_count_;
            }
        }
    }

public:
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr) {};
    explicit shared_ptr(T *ptr) : ptr_(ptr), ref_count_(new size_t(1)) {}

    shared_ptr(const shared_ptr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_)
    {
        if (ref_count_)
        {
            (*ref_count_)++;
        }
    }

    shared_ptr(const shared_ptr &&other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_)
    {
        ptr_ = nullptr;
        ref_count_ = nullptr;
    }

    shared_ptr &operator=(const shared_ptr &other)
    {
        if (this != &other)
        {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (*ref_count_)
            {
                (*ref_count_)++;
            }
        }
        return this;
    }
    shared_ptr &operator=(const shared_ptr &&other) noexcept
    {
        if (this != &other)
        {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    ~shared_ptr()
    {
        release();
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    T *get() const
    {
        return ptr_;
    }

    size_t use_count() const
    {
        return ref_count_ ? *ref_count_ : 0;
    }

    bool empty() const
    {
        return ptr_ == nullptr;
    }
    void reset()
    {
        release();
        ptr_ = nullptr;
        ref_count_ = nullptr;
    }

    void reset(T *p)
    {
        release();
        ptr_ = p;
        ref_count_ = p ? new size_t(1) : nullptr;
    }

    explicit operator bool()
    {
        return ptr_ != nullptr;
    }

    bool operator==(const shared_ptr &other)
    {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const shared_ptr &other)
    {
        return ptr_ != other.ptr_;
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args &&...args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}