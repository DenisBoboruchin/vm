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

    class iterator;
    
    void push_front(const T &value);
    void push_back(const T &value);

    void pop_front();
    void pop_back();

    T &front() &;
    const T &front() const &;

    T &back() &;
    const T &back() const &;

    iterator find(const T &value);

    bool remove(const T &value);

    size_t size() const;
    bool empty() const;

    iterator begin() const;
    iterator end() const;

private:
    struct list_node_t final {
        T data_ {};
        list_node_t *next_ = nullptr;
        list_node_t *prev_ = nullptr;
    };

    void delete_data_();

    list_node_t *push_(const T &value);
    list_node_t *pop_(list_node_t *deletable);
    void pop_last_();

    size_t size_ = 0;
    list_node_t *rear_ = nullptr;
    list_node_t *front_ = nullptr;
};

template <typename T>
class list<T>::iterator final {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using reference = T &;
    using pointer = T *;

    explicit iterator(list_node_t *node_ptr = nullptr);

    iterator &operator++();
    iterator &operator++(int);
    iterator &operator--();
    iterator &operator--(int);

    reference operator*() const;
    pointer operator->() const;

    auto operator<=>(const iterator &other) const = default;

    list_node_t *get_ptr_ ();

private:
    list_node_t *node_itr_;
};

template <typename T>
list<T>::iterator::iterator(list_node_t *node_ptr) : node_itr_ {node_ptr}
{
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator++()
{
    node_itr_ = node_itr_->next_;

    return *this;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator++(int)
{
    auto temp {*this};
    operator++();

    return temp;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator--()
{
    node_itr_ = node_itr_->prev_;

    return *this;
}

template <typename T>
typename list<T>::iterator &list<T>::iterator::operator--(int)
{
    auto temp {*this};
    operator--();

    return temp;
}

template <typename T>
typename list<T>::iterator::reference list<T>::iterator::operator*() const
{
    return node_itr_->data_;
}

template <typename T>
typename list<T>::iterator::pointer list<T>::iterator::operator->() const
{
    return &(node_itr_->data_);
}

template <typename T>
typename list<T>::list_node_t* list<T>::iterator::get_ptr_()
{
    return node_itr_;
}

template <typename T>
list<T>::list(const list<T> &other) : list()
{
    list_node_t *temp = other.rear_;

    while (temp) {
        push_front(temp->data_);

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

    list_node_t *temp = other.rear_;

    while (temp) {
        push_front(temp->data_);

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
    while (rear_) {
        list_node_t *temp = rear_->next_;

        delete rear_;
        rear_ = temp;
    }
}

template <typename T>
void list<T>::push_back(const T &value)
{
    list_node_t *new_list_node = new list_node_t {value};

    if (empty()) {
        front_ = new_list_node;
        new_list_node->next_ = nullptr;
    } else {
        new_list_node->next_ = rear_;
        rear_->prev_ = new_list_node;
    }

    rear_ = new_list_node;
    new_list_node->prev_ = nullptr;

    size_++;
}

template <typename T>
void list<T>::push_front(const T &value)
{
    list_node_t *new_list_node = new list_node_t {value};

    if (empty()) {
        rear_ = new_list_node;
        new_list_node->prev_ = nullptr;
    } else {
        new_list_node->prev_ = front_;
        front_->next_ = new_list_node;
    }

    front_ = new_list_node;
    new_list_node->next_ = nullptr;

    size_++;
}

template <typename T>
void list<T>::pop_back()
{
    if (size_ < 2) {
        pop_last_();
        return;
    }

    list_node_t *new_rear = rear_->next_;
    new_rear->prev_ = nullptr;
    delete rear_;

    rear_ = new_rear;
    size_--;
}

template <typename T>
void list<T>::pop_front()
{
    if (size_ < 2) {
        pop_last_();
        return;
    }

    list_node_t *new_front = front_->prev_;
    new_front->next_ = nullptr;
    delete front_;

    front_ = new_front;
    size_--;
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
    auto node_itr = find(value);
    list_node_t* node_ptr = node_itr.get_ptr_ ();

    if (!node_ptr) {
        return 0;
    }

    if (node_itr == begin ()) {
        pop_back();
    } else if (node_itr == static_cast<list<T>::iterator> (front_)) {
        pop_front();
    } else {
        node_ptr->next_->prev_ = node_ptr->prev_;
        node_ptr->prev_->next_ = node_ptr->next_;

        delete node_ptr;
        size_--;
    }

    return 1;
}

template <typename T>
typename list<T>::iterator list<T>::find(const T &value)
{
    auto end_itr = end();
    for (auto itr = begin (); itr != end_itr; ++itr)
    {
        if (*itr == value)
        {
            return itr;
        }
    }

    return end_itr;
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
typename list<T>::iterator list<T>::begin() const
{
    return iterator {list<T>::rear_};
}

template <typename T>
typename list<T>::iterator list<T>::end() const
{
    return iterator {};
}

}  // namespace my_containers
#endif
