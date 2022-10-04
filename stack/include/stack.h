#pragma once

#include <iostream>
#include <cstring>

namespace my_containers
{

const size_t MIN_CAPACITY = 128;
const double CAPACITY_FACTOR = 2;
const int RATIO_TO_RESIZE_DOWN = 4;


template <typename T> class stack 
{
public:
    stack (size_t capacity = MIN_CAPACITY);
    stack (const stack& other);
    stack (stack&& other);

    ~stack ();
    
    stack& operator= (const stack& other);
    stack& operator= (stack&& other);

    void push (const T& elem);
    void pop ();
    T& top () const &;

    bool empty () const;
    size_t size () const;     

private:
    void check_size_ ();
    
    void resize_up_ ();
    void resize_down_ ();

private:
    size_t capacity_ = 0;
    size_t size_ = 0;

    T* data_ = nullptr;
};


template <typename T> stack<T>::stack (size_t capacity): capacity_ {capacity}
{
    data_ = new T[capacity];
}

template <typename T> stack<T>::stack (const stack& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;

	data_ = new T[capacity_];
	memcpy (data_, other.data_, sizeof (T));
}

template <typename T> stack<T>::stack (stack&& other)
{
    *this = std::move(other);
}

template <typename T> stack<T>::~stack ()
{
    delete [] data_;
}

template <typename T> stack<T>& stack<T>::operator= (const stack& other) 
{
    capacity_ = other.capacity_;
    size_ = other.size_;
    
    delete [] data_;
    data_ = new T[capacity_];
    memcpy (data_, other.data_, sizeof (T));

    return *this;
}

template <typename T> stack<T>& stack<T>::operator= (stack&& other)
{
    if (this != &other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        std::swap(data_, other.data_);
    }

    return *this;
}

template <typename T> void stack<T>::push (const T& elem)
{
    this->check_size_ ();

    data_[size_] = elem;
    size_++;
}

template <typename T> void stack<T>::pop ()
{
    this->check_size_ ();

    size_--;
}

template <typename T> T& stack<T>::top () const &
{
	return data_[size_];
}

template <typename T> bool stack<T>::empty () const
{
    return size_;
}

template <typename T> size_t stack<T>::size () const
{
    return size_;
}      

template <typename T> void stack<T>::check_size_ ()
{
    if (size_ == capacity_)
        this->resize_up_ ();

    else if (size_ < size_t (capacity_ / RATIO_TO_RESIZE_DOWN))
        this->resize_down_ ();
}

template <typename T> void stack<T>::resize_up_ ()
{
    T* new_data = new T[int (capacity_ * CAPACITY_FACTOR)];   

    memcpy (new_data, data_, sizeof (T));
    delete [] data_;

    data_ = new_data;
}

template <typename T> void stack<T>::resize_down_ ()
{
    if (size_ > 2 * MIN_CAPACITY)
    {
        T* new_data = new T[int (capacity_ / CAPACITY_FACTOR)];

        memcpy (new_data, data_, sizeof (T));
        delete [] data_;

        data_ = new_data;
    }   
}

}
