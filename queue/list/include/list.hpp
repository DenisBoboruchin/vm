#include <iostream>

namespace my_containers {

template <typename T>
class list final {
public:
    list() {};
    list(const list &other);
    list(list&& other) noexcept;

    list& operator= (const list& other);
    list& operator= (list&& other) noexcept;

    ~list();

    void push_front(const T &value);
    void push_back(const T &value);

    void pop_front();
    void pop_back();

    T &front() &;
    const T& front () const &;
    
    T &back() &;
    const T& back () const &;

    size_t size() const;
    bool empty() const;

private: 
    struct node final {
        T data_ {};
        node *next_ = nullptr;
        node *prev_ = nullptr;
    };

    void delete_data_ ();

    node* push_ (const T& value);
    void pop_last_ ();

    size_t size_ = 0;
    node *rear_ = nullptr;
    node *front_ = nullptr;
};

template <typename T>
list<T>::list(const list<T> &other) : list ()
{
    node *temp = other.front_;
    size_t full_size = other.size_;

    while (size_ != full_size) {
        push_back(temp->data_);

        temp = temp->next_;
    }
}

template <typename T>
list<T>::list (list<T>&& other) noexcept
{
    std::swap (size_, other.size_);
    std::swap (rear_, other.rear_);
    std::swap (front_, other.front_);
}

template <typename T>
list<T>& list<T>::operator= (const list<T>& other)
{ 
    if (this == &other)
        return *this;

    delete_data_ ();
 
    size_ = 0;
    rear_ = nullptr;
    front_ = nullptr;

    node* temp = other.front_;
    size_t full_size = other.size_;

    while (size_ != full_size)
    {
        push_back(temp->data_);

        temp = temp->next_;
    }   

    return *this;
}

template <typename T>
list<T>& list<T>::operator= (list<T>&& other) noexcept
{
    std::swap (size_, other.size_);
    std::swap (rear_, other.rear_);
    std::swap (front_, other.front_);

    return *this;
}

template <typename T>
list<T>::~list()
{
    delete_data_ ();
}

template <typename T>
void list<T>::delete_data_ ()
{
    if (!front_)
        return;

    front_->prev_->next_ = nullptr;
    while (front_) {
        node *temp = front_->next_;

        delete front_;
        front_ = temp;
    }
}

template <typename T>
void list<T>::push_back(const T &value)
{
    rear_ = push_ (value);
}

template <typename T>
void list<T>::push_front(const T &value)
{
    front_ = push_ (value);
}

template <typename T>
typename list<T>::node* list<T>::push_ (const T & value)
{
    node *new_node = new node {value};

    if (!rear_)
        rear_ = front_ = new_node;

    new_node->prev_ = rear_;
    new_node->next_ = front_;
    front_->prev_ = new_node;
    rear_->next_ = new_node;

    size_++;
    return new_node;
}

template <typename T>
void list<T>::pop_back()
{
    if (!rear_)
        return;

    if (size_ == 1)
        return pop_last_ ();

    node* new_rear = rear_->prev_;

    delete rear_;
    rear_ = new_rear;
    rear_->next_ = front_;
    front_->prev_ = rear_;

    size_--;
}

template <typename T>
void list<T>::pop_front()
{
    if (!front_)
        return;

    if (size_ == 1)
        return pop_last_ ();

    node* new_front = front_->next_;

    delete front_;
    front_ = new_front;
    front_->prev_ = rear_;
    rear_->next_ = front_;

    size_--;
}

template <typename T>
void list<T>::pop_last_()
{
    delete front_;
    front_ = rear_ = nullptr;

    size_--;
}

template <typename T>
T &list<T>::front() &
{
    return front_->data_;
}

template <typename T>
const T &list<T>::front() const &
{
    return front_->data_;
}

template <typename T>
T &list<T>::back() &
{
    return rear_->data_;
}

template <typename T>
const T &list<T>::back() const &
{
    return rear_->data_;
}

template <typename T>
size_t list<T>::size() const
{
    return size_;
}

template <typename T>
bool list<T>::empty() const
{
    return size_ == 0;
}

}  // namespace my_containers
