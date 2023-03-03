#ifndef LIST_LIST_HPP
#define LIST_LIST_HPP

#include <iostream>
#include <iterator>

namespace my_containers {

template <typename T>
class list final {
public:
    list() {};
    list(const list &other);
    list(list &&other) noexcept;

    list &operator=(const list &other);
    list &operator=(list &&other) noexcept;

    ~list();

    void push_front(const T &value);
    void push_back(const T &value);

    void pop_front();
    void pop_back();

    T &front() &;
    const T &front() const &;

    T &back() &;
    const T &back() const &;

    bool find(const T &value);

    T& get_elem (const T& value) &;
    const T& get_elem (const T& value) const &;

    bool remove(const T &value);

    size_t size() const;
    bool empty() const;

    class iterator;
    
    iterator begin () const;
    iterator end () const;

private:
    struct list_node_t final {
        T data_ {};
        list_node_t *next_ = nullptr;
        list_node_t *prev_ = nullptr;
    };

    void delete_data_();

    list_node_t *find_ptr_(const T &value);

    list_node_t *push_(const T &value);
    list_node_t *pop_(list_node_t *deletable);
    void pop_last_();

    size_t size_ = 0;
    list_node_t *rear_ = nullptr;
    list_node_t *front_ = nullptr;
};

template <typename T>
class list<T>::iterator final
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using reference = T&;
    using pointer = T*; 

    iterator (list_node_t* node_ptr = nullptr);

    iterator& operator++ (); 
    iterator& operator++ (int);

    reference operator* () const;
    pointer operator-> () const;

    auto operator <=> (const iterator& other) const = default;

private:
    list_node_t* node_itr_;
};

template <typename T>
list<T>::iterator::iterator (list_node_t* node_ptr) : node_itr_ {node_ptr} 
{}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++ ()
{
    node_itr_ = node_itr_->next_;
    
    return *this;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++ (int)
{
    auto temp {*this};
    operator++();

    return temp;
}

template <typename T>
typename list<T>::iterator::reference list<T>::iterator::operator* () const
{
    return node_itr_->data_;
}

template <typename T>
typename list<T>::iterator::pointer list<T>::iterator::operator-> () const
{
    return &(node_itr_->data_);
}

template <typename T>
list<T>::list(const list<T> &other) : list()
{
    list_node_t *temp = other.front_;
    size_t full_size = other.size_;

    while (size_ != full_size) {
        push_back(temp->data_);

        temp = temp->next_;
    }
}

template <typename T>
list<T>::list(list<T> &&other) noexcept
{
    std::swap(size_, other.size_);
    std::swap(rear_, other.rear_);
    std::swap(front_, other.front_);
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &other)
{
    if (this == &other) {
        return *this;
    }

    delete_data_();

    size_ = 0;
    rear_ = nullptr;
    front_ = nullptr;

    list_node_t *temp = other.front_;
    size_t full_size = other.size_;

    while (size_ != full_size) {
        push_back(temp->data_);

        temp = temp->next_;
    }

    return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&other) noexcept
{
    std::swap(size_, other.size_);
    std::swap(rear_, other.rear_);
    std::swap(front_, other.front_);

    return *this;
}

template <typename T>
list<T>::~list()
{
    delete_data_();
}

template <typename T>
void list<T>::delete_data_()
{
    if (!front_) {
        return;
    }

    front_->prev_->next_ = nullptr;
    while (front_) {
        list_node_t *temp = front_->next_;

        delete front_;
        front_ = temp;
    }
}

template <typename T>
void list<T>::push_back(const T &value)
{
    rear_ = push_(value);
}

template <typename T>
void list<T>::push_front(const T &value)
{
    front_ = push_(value);
}

template <typename T>
typename list<T>::list_node_t *list<T>::push_(const T &value)
{
    list_node_t *new_list_node_t = new list_node_t {value};

    if (!rear_) {
        rear_ = front_ = new_list_node_t;
    }

    new_list_node_t->prev_ = rear_;
    new_list_node_t->next_ = front_;
    front_->prev_ = new_list_node_t;
    rear_->next_ = new_list_node_t;

    size_++;
    return new_list_node_t;
}

template <typename T>
void list<T>::pop_back()
{
    list_node_t *front_ptr = pop_(rear_);

    if (front_ptr) {
        rear_ = front_ptr->prev_;
    }
}

template <typename T>
void list<T>::pop_front()
{
    front_ = pop_(front_);
}

template <typename T>
typename list<T>::list_node_t *list<T>::pop_(list<T>::list_node_t *deletable)
{
    if (size_ < 2) {
        pop_last_();
        return nullptr;
    }

    list_node_t *next = deletable->next_;
    list_node_t *prev = deletable->prev_;
    delete deletable;

    prev->next_ = next;
    next->prev_ = prev;

    size_--;

    return next;
}

template <typename T>
void list<T>::pop_last_()
{
    if (!rear_) {
        return;
    }

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
bool list<T>::remove(const T &value)
{
    list_node_t *elem = find_ptr_(value);

    if (elem) {
        list_node_t *front_ptr = pop_(elem);

        if ((elem == rear_) && front_ptr) {
            rear_ = front_ptr->prev_;
        }

        else if (elem == front_) {
            front_ = front_ptr;
        }

        return 1;
    }

    return 0;
}

template <typename T>
typename list<T>::list_node_t *list<T>::find_ptr_(const T &value)
{
    list_node_t *work_list_node = front_;

    while (work_list_node != rear_) {
        if (work_list_node->data_ == value)
            return work_list_node;

        work_list_node = work_list_node->next_;
    }

    return nullptr;
}

template <typename T>
bool list<T>::find(const T &value)
{
    list_node_t *elem_ptr = find_ptr_(value);

    if (elem_ptr)
        return 1;

    return 0;
}

template <typename T>
T& list<T>::get_elem(const T& value) & 
{
    list_node_t* elem_ptr = find_ptr_(value);
    
    if (elem_ptr)
    {
        return elem_ptr->data_;
    }
    else
    {
        return rear_->data_;
    }
}

template <typename T>
const T& list<T>::get_elem(const T& value) const & 
{
    list_node_t* elem_ptr = find_ptr_(value);

    if (elem_ptr)
        return elem_ptr->data_;
    else 
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

template <typename T> 
typename list<T>::iterator list<T>::begin () const
{
    return iterator {list<T>::front_}; 
}

template <typename T> 
typename list<T>::iterator list<T>::end () const
{
    return iterator {list<T>::rear_}; 
}

}  // namespace my_containers
#endif
