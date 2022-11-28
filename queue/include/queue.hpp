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

    virtual const T& front () const & = 0;
    //virtual const T& back () const & = 0;

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

    const T& front () const & override;
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

    const T& front () const & override;
    //const T& back () const & override;

    size_t size () const override;
    bool empty () const override;

private:
    void change_used_stack1_ ();
    void change_used_stack2_ ();

    stack<T> stack1_;
    stack<T> stack2_;
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
void queue_stacks<T>::change_used_stack2_ ()
{
    while (!stack1_.empty ())
    {
        stack2_.push (stack1_.top ());
        stack1_.pop();
    } 
}

template <typename T>
void queue_stacks<T>::change_used_stack1_ ()
{
    while (!stack2_.empty ())
    {
        stack1_.push (stack2_.top ());
        stack2_.pop();
    }
}

template <typename T>
void queue_stacks<T>::push (const T& value)
{
    change_used_stack2_ ();
    stack1_.push (value);

    change_used_stack1_ ();
}

template <typename T>
void queue_stacks<T>::pop ()
{
    stack1_.pop ();
}

template <typename T>
T& queue_stacks<T>::front () &
{
    return stack1_.top ();
}

template <typename T>
const T& queue_stacks<T>::front () const &
{
    return stack1_.top ();
}

template <typename T>
T& queue_stacks<T>::back () &
{
    change_used_stack2_ ();
    T& back_val = stack2_.top ();

    change_used_stack1_ ();
    return back_val;
}
#if 0
template <typename T>
const T& queue_stacks<T>::back () const &
{
    change_used_stack2_ ();
    const T& back_val = stack2_.top ();

    change_used_stack1_ ();
    return back_val;
}
#endif
template <typename T>
size_t queue_stacks<T>::size () const
{
    return stack1_.size ();
}

template <typename T>
bool queue_stacks<T>::empty () const
{
    return stack1_.empty ();
}
}

#endif
