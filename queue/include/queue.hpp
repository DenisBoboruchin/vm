#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"
#include "stack.hpp"

namespace my_containers
{

template <typename T>
class Iqueue 
{
public:
    virtual ~Iqueue() {};

    virtual void push (const T& value) = 0;
    virtual void pop () = 0;

    virtual T& front () & = 0;
    virtual T& back () & = 0;

    virtual size_t size () const = 0;
    virtual bool empty () const = 0;
};

template <typename T>
class queue_list final : public Iqueue<T> 
{
public:
    void push (const T& value) override;
    void pop () override;

    T& front () & override;
    T& back () & override;

    const T& front () const &;
    const T& back () const &;

    size_t size () const override;
    bool empty () const override;

private:
    list<T> list_ {}; 
};

template <typename T>
class queue_stacks final : public Iqueue<T>
{
public:
    void push (const T& value) override;
    void pop () override;

    T& front () & override;
    T& back () & override;

    size_t size () const override;
    bool empty () const override;

private:
    bool push_stack_used_ ();
    void change_used_stack_push_ ();
    void change_used_stack_pop_ ();

    size_t size_ = 0;
    size_t num_pops_ = 0;

    stack<T> stack_push_;
    stack<T> stack_pop_;
};

template <typename T>
void queue_list<T>::push (const T& value)
{
    list_.push_back (value);
}

template <typename T>
void queue_list<T>::pop ()
{
    list_.pop_front ();
}

template <typename T>
T& queue_list<T>::front () &
{
    return list_.front ();
}

template <typename T>
const T& queue_list<T>::front () const &
{
    return list_.front ();
}

template <typename T>
T& queue_list<T>::back () &
{
    return list_.back ();
}

template <typename T>
const T& queue_list<T>::back () const &
{
    return list_.back ();
}

template <typename T>
size_t queue_list<T>::size () const
{
    return list_.size ();
}

template <typename T>
bool queue_list<T>::empty () const
{
    return list_.empty ();
}

template <typename T>
bool queue_stacks<T>::push_stack_used_ ()
{
    return (!stack_push_.empty ());
}

template <typename T>
void queue_stacks<T>::change_used_stack_pop_ ()
{
    while (!stack_push_.empty ())
    {
        stack_pop_.push (stack_push_.top ());
        stack_push_.pop();
    } 
}

template <typename T>
void queue_stacks<T>::change_used_stack_push_ ()
{
    while (!stack_pop_.empty ())
    {
        stack_push_.push (stack_pop_.top ());
        stack_pop_.pop();
    }
}

template <typename T>
void queue_stacks<T>::push (const T& value)
{
#if 0
    change_used_stack_pop_ ();
    stack_push_.push (value);

    change_used_stack_push_ ();
#endif 
    if (!push_stack_used_ ())
        change_used_stack_push_ ();

    stack_push_.push (value);
    size_++;
}

template <typename T>
void queue_stacks<T>::pop ()
{
    if (push_stack_used_ ())
        num_pops_++; 
    else
        stack_pop_.pop ();
    
    size_--;
    //stack_push_.pop ();
}

template <typename T>
T& queue_stacks<T>::front () &
{
    if (push_stack_used_ ())
        change_used_stack_pop_ ();

    while (num_pops_)
    {
        stack_pop_.pop ();
        num_pops_--;
    }

    return stack_pop_.top ();

    //return stack_push_.top ();
}

template <typename T>
T& queue_stacks<T>::back () &
{
    if (!push_stack_used_ ())
        change_used_stack_push_ ();
        
    return stack_push_.top ();

#if 0
    change_used_stack_pop_ ();
    T& back_val = stack_pop_.top ();

    change_used_stack_push_ ();
    return back_val;
#endif
}

template <typename T>
size_t queue_stacks<T>::size () const
{
    return size_;
}

template <typename T>
bool queue_stacks<T>::empty () const
{
    return size_ == 0;
}

}

#endif
