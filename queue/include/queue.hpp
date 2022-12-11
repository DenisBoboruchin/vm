#ifndef QUEUE_QUEUE_HPP
#define QUEUE_QUEUE_HPP

#include "list.hpp"
#include "stack.hpp"

namespace my_containers {

template <typename T>
class Iqueue {
public:
    virtual ~Iqueue() = default;

    virtual void push(const T &value) = 0;
    virtual void pop() = 0;

    virtual T &front() & = 0;
    virtual T &back() & = 0;

    virtual const T &front() const & = 0;
    virtual const T &back() const & = 0;

    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
};

template <typename T>
class queue_list final : public Iqueue<T> {
public:
    queue_list () = default;
    queue_list (const queue_list& other) = default;
    queue_list (queue_list&& other) = default;

    queue_list& operator= (const queue_list& other) = default;
    queue_list& operator= (queue_list&& other) = default; 

    void push(const T &value) override;
    void pop() override;

    T &front() & override;
    T &back() & override;

    const T &front() const & override;
    const T &back() const & override;

    size_t size() const override;
    bool empty() const override;

private:
    list<T> list_ {};
};

template <typename T>
class queue_stacks final : public Iqueue<T> {
public:
    queue_stacks () = default;
    queue_stacks (const queue_stacks& other) = default;
    queue_stacks (queue_stacks&& other) = default;

    queue_stacks& operator= (const queue_stacks& other) = default;
    queue_stacks& operator= (queue_stacks&& other) = default; 

    void push(const T &value) override;
    void pop() override;

    T &front() & override;
    T &back() & override;

    const T &front() const & override;
    const T &back() const & override;

    size_t size() const override;
    bool empty() const override;

private:
    void move_elems_to_stack_pop_();

    stack<T> stack_push_;
    stack<T> stack_pop_;
};

template <typename T>
void queue_list<T>::push(const T &value)
{
    list_.push_back(value);
}

template <typename T>
void queue_list<T>::pop()
{
    list_.pop_front();
}

template <typename T>
T &queue_list<T>::front() &
{
    return list_.front();
}

template <typename T>
const T &queue_list<T>::front() const &
{
    return list_.front();
}

template <typename T>
T &queue_list<T>::back() &
{
    return list_.back();
}

template <typename T>
const T &queue_list<T>::back() const &
{
    return list_.back();
}

template <typename T>
size_t queue_list<T>::size() const
{
    return list_.size();
}

template <typename T>
bool queue_list<T>::empty() const
{
    return list_.empty();
}

template <typename T>
void queue_stacks<T>::move_elems_to_stack_pop_()
{
    while (!stack_push_.empty()) {
        stack_pop_.push(stack_push_.top());
        stack_push_.pop();
    }
}

template <typename T>
void queue_stacks<T>::push(const T &value)
{
    stack_push_.push(value);
}

template <typename T>
void queue_stacks<T>::pop()
{
    if (stack_pop_.empty() && !stack_push_.empty()) {
        if (stack_push_.size() == 1) {
            return stack_push_.pop();
        }

        move_elems_to_stack_pop_();
    }

    stack_pop_.pop();
}

template <typename T>
const T &queue_stacks<T>::front() const &
{
    if (!stack_pop_.empty()) {
        return stack_pop_.top();
    }

    return stack_push_.down();
}

template <typename T>
const T &queue_stacks<T>::back() const &
{
    if (!stack_push_.empty()) {
        return stack_push_.top();
    }

    return stack_pop_.down();
}

template <typename T>
T &queue_stacks<T>::front() &
{
    if (!stack_pop_.empty()) {
        return stack_pop_.top();
    }

    return stack_push_.down();
}

template <typename T>
T &queue_stacks<T>::back() &
{
    if (!stack_push_.empty()) {
        return stack_push_.top();
    }

    return stack_pop_.down();
}

template <typename T>
size_t queue_stacks<T>::size() const
{
    return stack_push_.size() + stack_pop_.size();
}

template <typename T>
bool queue_stacks<T>::empty() const
{
    return stack_push_.empty() && stack_pop_.empty();
}

}  // namespace my_containers

#endif
