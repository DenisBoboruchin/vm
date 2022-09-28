#pragma once

#include <iostream>
#include <cstring>

namespace my_containers
{

const size_t MIN_CAPACITY = 10;
const size_t BIG_CAPACITY = 500;

const double CAPACITY_FACTOR = 1.4;
const int CAPACITY_ADDED = 100;

template <typename T> class stack 
{
public:
    stack (size_t capacity): capacity_ {capacity}
    {
        data_ = new T[capacity];
    }

    stack (const stack& other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
    
        data_ = new T[capacity_];
        memcpy (data_, other.data_, sizeof (T));
    }

    ~stack ()
    {
        delete [] data_;
    }

    stack& operator= (const stack& other) 
    {
        capacity_ = other.capacity_;
        size_ = other.size_;

        data_ = new T[capacity_];
        memcpy (data_, other.data_, sizeof (T));

        return *this;
    }

    void push (const T& elem)
    {
        this->check_size_ ();

        size_++;
        data_[size_] = elem;
    }

    void pop ()
    {
        this->check_size_ ();

        size_--;
    }

    T& top () const
    {
        return data_[size_];
    }

    bool empty () const
    {
        return size_ == 0;
    }

    size_t size () const
    {
        return size_;
    }       

private:
    void check_size_ ()
    {
        if (size_ == capacity_)
        {
            this->resize_up_ ();
        }

        else if (size_ < size_t (capacity_ / 2))
        {
            if (size_ > 2 * MIN_CAPACITY)
                //this->resize_down_ ();
            {}
        }
    }

    void resize_up_ ()
    {
        if (capacity_ < size_t (BIG_CAPACITY))
        {
            T* new_data = new T[int (capacity_ * CAPACITY_FACTOR)];   

            memcpy (new_data, data_, sizeof (T));
            delete [] data_;

            data_ = new_data;
        }

        else
        {
            T* new_data = new T[capacity_ + size_t (CAPACITY_ADDED)];

            memcpy (new_data, data_, sizeof (T));   
            delete [] data_;

            data_ = new_data;
        }
    }

    size_t capacity_ = 0;
    size_t size_ = 0;

    T* data_ = nullptr;
};

}
