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
    virtual const T& back () const & = 0;

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
    const T& back () const & override;

    size_t size () const override;
    bool empty () const override;

private:
    list<T> list_ {}; 
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

}

#endif
