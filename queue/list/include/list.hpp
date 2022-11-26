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

    void push(const T &value);
    void push(T &&value);
    void pop();

    T &front() &;
    const T& front () const &;
    
    T &back() &;
    const T& back () const &;

    size_t size() const;
    bool empty() const;

private:
    void delete_data_ ();

    template <typename U>
    struct node {
        U data_ {};
        node<U> *next_ = nullptr;
    };

    size_t size_ = 0;
    node<T> *rear_ = nullptr;
    node<T> *front_ = nullptr;
};

template <typename T>
list<T>::list(const list<T> &other) : list ()
{
    node<T> *temp = other.front_;
    while (temp) {
        push(temp->data_);

        temp = temp->next_;
    }
}

template <typename T>
list<T>::list (list<T>&& other) noexcept : size_ {other.size_}, 
    rear_ {std::move (other.rear_)}, front_ {std::move (other.front_)}
{
    other.rear_ = nullptr;
    other.front_ = nullptr;
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

    node<T>* temp = other.front_;
    while (temp)
    {
        push(temp->data_);

        temp = temp->next_;
    }   

    return *this;
}

template <typename T>
list<T>& list<T>::operator= (list<T>&& other) noexcept
{
    if (this != &other)
    {
        size_ = other.size_;
        std::swap (rear_, other.rear_);
        std::swap (front_, other.front_);
    }

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
    while (front_) {
        node<T> *temp = front_->next_;

        delete front_;
        front_ = temp;
    }

}

template <typename T>
void list<T>::push(const T &value)
{
    node<T> *new_node = new node<T> {value};

    if (!rear_)
        rear_ = front_ = new_node;

    rear_->next_ = new_node;
    rear_ = new_node;
    size_++;
}

template <typename T>
void list<T>::push(T &&value)
{
    node<T> *new_node = new node<T> {std::move(value)};

    if (!rear_)
        rear_ = front_ = new_node;

    rear_->next_ = new_node;
    rear_ = new_node;
    size_++;
}

template <typename T>
void list<T>::pop()
{
    if (!front_)
        return;

    auto new_front = front_->next_;

    delete front_;
    front_ = new_front;

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
