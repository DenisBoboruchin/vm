#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstring>
#include <climits>

namespace my_containers {

template <typename T>
class stack {
public:
    static constexpr const size_t MIN_CAPACITY = 128;
    static constexpr const double CAPACITY_FACTOR = 2;

    explicit stack(size_t capacity = MIN_CAPACITY);
    stack(const stack &other);
    stack(stack &&other);

    ~stack();

    stack &operator=(const stack &other);
    stack &operator=(stack &&other);

    void push(const T &elem);
    void pop();
    T &top() const &;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

private:
    void check_size_();

    void resize_up_();
    void resize_down_();

private:
    size_t capacity_ = 0;
    size_t size_ = 0;

    T *data_ = nullptr;
};

template <typename T>
const size_t stack<T>::MIN_CAPACITY;

template <typename T>
const double stack<T>::CAPACITY_FACTOR;

template <typename T>
stack<T>::stack(size_t capacity) : capacity_ {capacity}, data_ {new T[capacity]}

{
}

template <typename T>
stack<T>::stack(const stack &other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;

    data_ = new T[capacity_];
    memcpy(data_, other.data_, sizeof(T));
}

template <typename T>
stack<T>::stack(stack &&other)
{
    *this = std::move(other);
}

template <typename T>
stack<T>::~stack()
{
    delete[] data_;
}

template <typename T>
stack<T> &stack<T>::operator=(const stack &other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] data_;
    data_ = new T[capacity_];
    memcpy(data_, other.data_, sizeof(T));

    return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&other)
{
    if (this != &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        std::swap(data_, other.data_);
    }

    return *this;
}

template <typename T>
void stack<T>::push(const T &elem)
{
    this->check_size_();

    data_[size_] = elem;
    size_++;
}

template <typename T>
void stack<T>::pop()
{
    if (size_ > 0)
        size_--;
}

template <typename T>
T &stack<T>::top() const &
{
    return data_[size_ - 1];
}

template <typename T>
bool stack<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
size_t stack<T>::size() const
{
    return size_;
}

template <typename T>
size_t stack<T>::capacity() const
{
    return capacity_;
}

template <typename T>
void stack<T>::check_size_()
{
    if (size_ == capacity_)
        this->resize_up_();
}

template <typename T>
void stack<T>::resize_up_()
{
    capacity_ = capacity_ * CAPACITY_FACTOR;
    T *new_data = new T[capacity_];

    memcpy(new_data, data_, sizeof(T) * size_);
    delete[] data_;

    data_ = new_data;
}

}  // namespace my_containers

#endif
