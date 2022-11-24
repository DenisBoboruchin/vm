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

    T& front ();
    const T& front () const;

private:
    size_t size_ = 0;
    q_node<T>* rear_ = nullptr;
    q_node<T>* front_ = nullptr;
};

template <typename T> 
queue_list<T>::~queue_list ()
{
    q_node<T>* temp = rear_->next_;
    for (int count = 0; count != size_ - 1; ++count)
    {
        delete rear_;
        rear_ = temp;
        temp = rear_->next_;
    }

    delete rear_;
}

template <typename T>
void queue_list<T>::push (const T& value)
{   
    q_node<T>* node = new q_node<T> {value, rear_};

    if (rear_ == nullptr)
        rear_ = front_ = node;

    rear_ = node;
    size_++;
}

template <typename T>
T& queue_list<T>::front ()
{
    if (size_)
        return front_->data_;
}

template <typename T> 
const T& queue_list<T>::front () const
{
    if (size_)
        return front_->data_;
}

}   
