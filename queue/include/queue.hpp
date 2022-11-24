#include <iostream>

namespace my_containers 
{

template <typename T>
struct q_node
{
    T data_; 
    q_node<T>* next_ = nullptr;
};

template <typename T> 
class queue_list final
{   
public:
    
    ~queue_list ();
    
    void push (const T& value);
    void pop ();

    T& front () const &;
    T& back () const &;

    size_t size () const;
    bool empty () const;

private:
    size_t size_ = 0;
    q_node<T>* rear_ = nullptr;
    q_node<T>* front_ = nullptr;
};

template <typename T> 
queue_list<T>::~queue_list ()
{
    q_node<T>* temp = front_->next_;
    for (int count = 0; count != size_ - 1; ++count)
    {
        delete front_;
        front_ = temp;
        temp = front_->next_;
    }

    delete front_;
}

template <typename T>
void queue_list<T>::push (const T& value)
{   
    q_node<T>* node = new q_node<T> {value};

    if (rear_ == nullptr)
        rear_ = front_ = node;

    rear_->next_ = node;
    rear_ = node;
    size_++;
}

template <typename T>
void queue_list<T>::pop ()
{
    auto new_front = front_->next_;

    delete front_;
    front_ = new_front;

    size_--;
}

template <typename T>
T& queue_list<T>::front () const &
{
    if (size_)
        return front_->data_;
}

template <typename T>
T& queue_list<T>::back () const &
{
    if (size_)
        return rear_->data_;
}       

template <typename T>
size_t queue_list<T>::size () const
{
    return size_;
}

template <typename T>
bool queue_list<T>::empty () const
{
    return size_ == 0;
}

}   
