#include "stack.hpp"
#include <string.h>

namespace my_containers {

const int CHAR_BIT = 8;

template <>
class stack<bool> final {
public:
    static constexpr const size_t MIN_CAPACITY = 128;
    static constexpr const double CAPACITY_FACTOR = 2;

    stack();
    stack(const stack &other);
    stack(stack &&other) noexcept;

    ~stack();

    stack &operator=(const stack &other);
    stack &operator=(stack &&other) noexcept;

    void push(const bool &elem);
    void pop();
    bool top() const &;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

private:
    void check_size_();

    void resize_up_();
    void resize_down_();

private:
    static constexpr size_t CHAR_BIT = 8;

    size_t capacity_ = 0;
    size_t size_ = 0;

    char8_t *data_ = nullptr;
};

stack<bool>::stack() : capacity_ {MIN_CAPACITY}, data_ {new char8_t[(capacity_ - 1) / CHAR_BIT + 1]} {}

void stack<bool>::push(const bool &elem)
{
    check_size_();

    int num_char = static_cast<int>(size_ / CHAR_BIT);
    int num_bit = static_cast<int>(size_ % CHAR_BIT);

    if (elem)
        *(data_ + num_char) |= (1 << num_bit);
    else
        *(data_ + num_char) &= ~(1 << num_bit);

    size_++;
}

bool stack<bool>::top() const &
{
    int size = size_ - 1;
    int num_char = size / CHAR_BIT;
    int num_bit = size % CHAR_BIT;

    return (*(data_ + num_char) & (1 << num_bit)) != 0;
}

void stack<bool>::resize_up_()
{
    char8_t *new_data = new char8_t[(capacity_ * 2 - 1) / CHAR_BIT + 1];

    memcpy(new_data, data_, (size_ - 1) / CHAR_BIT + 1);
    delete[] data_;

    data_ = new_data;
}

}  // namespace my_containers
