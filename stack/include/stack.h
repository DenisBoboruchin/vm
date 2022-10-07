#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstring>
#include <climits>

namespace my_containers
{

const size_t MIN_CAPACITY = 128;
const double CAPACITY_FACTOR = 2;

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
    T top () const &;

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

/*
template <> class stack<bool>
{
private:
    char* data_ = nullptr;
};*/


template <typename T> stack<T>::stack (size_t capacity): capacity_ {capacity}
{
    data_ = new T[capacity];
}

template <> stack<bool>::stack (size_t capacity): capacity_ {capacity}
{
    data_ = new bool[(capacity - 1) / CHAR_BIT + 1];
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


template <> void stack<bool>::push (const bool& elem)
{
    this->check_size_ ();

    for (int i = CHAR_BIT - 1; i >= 0; i--)
    {
        printf ("%d", elem & (1 << i));
    }


    int blocks_bit = size_ / CHAR_BIT;
    int num_bit = size_ % CHAR_BIT;

    printf ("blocks_bit %d\n", blocks_bit);
    printf ("num_bit %d\n", num_bit);
    if (elem)
    {
        printf ("true\n");
        data_[blocks_bit] |= (1 << 1);
        printf ("insert %d\n", data_[blocks_bit] & (1 << num_bit));
    }

    else
        data_[blocks_bit] &= ~(1 << num_bit);

    for (int i = CHAR_BIT - 1; i >= 0; i--)
    {
        printf ("%d", data_[blocks_bit] & (1 << i));
    }
    printf ("\n");

    size_++;
}

template <typename T> void stack<T>::pop ()
{
    size_--;
}

template <typename T> T stack<T>::top () const &
{
	return data_[size_ - 1];
}

template <> bool stack<bool>::top () const &
{
    int size = size_ - 1;
    int blocks_bit = size / CHAR_BIT;
    int num_bit = size % CHAR_BIT;

    printf ("%d\n", data_[blocks_bit] & (1 << num_bit));
    return data_[blocks_bit] & (1 << num_bit);
}

template <typename T> bool stack<T>::empty () const
{
    return size_ == 0;
}

template <typename T> size_t stack<T>::size () const
{
    return size_;
}      

template <typename T> void stack<T>::check_size_ ()
{
    if (size_ == capacity_)
        this->resize_up_ ();
}

template <typename T> void stack<T>::resize_up_ ()
{
    capacity_ = capacity_ * CAPACITY_FACTOR;
    T* new_data = new T[capacity_];   

    memcpy (new_data, data_, sizeof (T) * size_);
    delete [] data_;

    data_ = new_data;
}

template <> void stack<bool>::resize_up_ ()
{
    bool* new_data = new bool[(capacity_ * 2 - 1) / CHAR_BIT + 1];

    memcpy (new_data, data_, sizeof (bool) * (size_ - 1));
    delete [] data_;

    data_ = new_data;
}

}

#endif

