#include "stack.hpp"
#include <cstring>

namespace my_containers {

stack<bool>::stack() : capacity_ {MIN_CAPACITY}, data_ {new char8_t[(capacity_ - 1) / BIT_CHAR + 1]} {}

stack<bool>::stack(const stack &other)
    : capacity_ {other.capacity_}, size_ {other.size_}, data_ {new char8_t[capacity_]}
{
    memcpy(data_, other.data_, sizeof(char8_t));
}

stack<bool>::stack(stack &&other) noexcept
{
    *this = std::move(other);
}

stack<bool>::~stack()
{
    delete[] data_;
}

stack<bool> &stack<bool>::operator=(const stack &other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] data_;
    data_ = new char8_t[capacity_];
    memcpy(data_, other.data_, sizeof(char8_t));

    return *this;
}

stack<bool> &stack<bool>::operator=(stack &&other) noexcept
{
    if (this != &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        std::swap(data_, other.data_);
    }

    return *this;
}

void stack<bool>::push(const bool &elem)
{
    check_size_();

    int num_char = static_cast<int>(size_ / BIT_CHAR);
    int num_bit = static_cast<int>(size_ % BIT_CHAR);

    if (elem)
        *(data_ + num_char) |= (1 << num_bit);
    else
        *(data_ + num_char) &= ~(1 << num_bit);

    size_++;
}

void stack<bool>::pop()
{
    if (size_ > 0)
        size_--;
}

bool stack<bool>::top() const &
{
    int size = size_ - 1;
    int num_char = size / BIT_CHAR;
    int num_bit = size % BIT_CHAR;

    return (*(data_ + num_char) & (1 << num_bit)) != 0;
}

bool stack<bool>::empty() const
{
    return size_ == 0;
}

size_t stack<bool>::size() const
{
    return size_;
}

size_t stack<bool>::capacity() const
{
    return capacity_;
}

void stack<bool>::check_size_()
{
    if (size_ == capacity_)
        this->resize_up_();
}

void stack<bool>::resize_up_()
{
    char8_t *new_data = new char8_t[(capacity_ * 2 - 1) / BIT_CHAR + 1];

    memcpy(new_data, data_, (size_ - 1) / BIT_CHAR + 1);
    delete[] data_;

    data_ = new_data;
}

}  // namespace my_containers
