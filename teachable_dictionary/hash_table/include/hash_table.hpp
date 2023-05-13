#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <utility>
#include <vector>

#include "list.hpp"

namespace my_containers {

template <typename Key, typename T, typename Hash = std::hash<Key>>
class hash_table final {
public:
    hash_table() {};

    hash_table(const hash_table &other);
    hash_table(hash_table &&other) noexcept;

    hash_table &operator=(const hash_table &other);
    hash_table &operator=(hash_table &&other) noexcept;

    ~hash_table() = default;

    using hash_table_node_t = typename std::pair<Key, T>;
    using iterator = typename list<hash_table_node_t>::iterator;

    iterator insert(const Key &key, const T &elem);
    iterator emplace(const Key &key, T &&elem);

    iterator erase(const Key &key);
    iterator find(const Key &key) const;

    size_t size() const;
    bool empty() const;

    iterator begin() const;
    iterator end() const;

private:
    using list_itr_t = typename list<hash_table_node_t>::iterator;
    using hash_itr_t = typename list<list_itr_t>::iterator;
    hash_itr_t find_hash_itr_(const Key &) const;

    void rehash_();
    void clear_hash_table_();
    void insert_in_hash_table_(const list_itr_t &elem_itr);

    size_t num_hash_buckets = 1024;

    list<hash_table_node_t> data_ {};

    std::vector<list<list_itr_t>> hash_table_ {num_hash_buckets};
};

template <typename Key, typename T, typename Hash>
hash_table<Key, T, Hash> &hash_table<Key, T, Hash>::operator=(const hash_table &other)
{
    if (this == &other)
        return *this;

    clear_hash_table_();
    for (auto elem : other)
        insert(elem.first, elem.second);

    return *this;
}

template <typename Key, typename T, typename Hash>
hash_table<Key, T, Hash>::hash_table(const hash_table<Key, T, Hash> &other)
{
    *this = other;
}

template <typename Key, typename T, typename Hash>
hash_table<Key, T, Hash> &hash_table<Key, T, Hash>::operator=(hash_table &&other) noexcept
{
    if (this == &other)
        return *this;

    std::swap(data_, other.data_);
    std::swap(hash_table_, other.hash_table_);

    return *this;
}

template <typename Key, typename T, typename Hash>
hash_table<Key, T, Hash>::hash_table(hash_table<Key, T, Hash> &&other) noexcept
{
    *this = other;
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::insert(const Key &key, const T &value)
{
    auto elem_itr = find(key);

    if (elem_itr != end()) {
        elem_itr->second = value;
        return elem_itr;
    }

    rehash_();

    data_.push_back({key, value});

    auto insert_itr = begin();
    int index = Hash {}(key) % num_hash_buckets;
    hash_table_.at(index).push_back(insert_itr);

    return insert_itr;
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::emplace(const Key &key, T &&value)
{
    auto elem_itr = find(key);

    if (elem_itr != end()) {
        elem_itr->second = std::forward<T>(value);
        return elem_itr;
    }

    rehash_();

    data_.emplace_back({key, std::forward<T>(value)});

    auto insert_itr = begin();
    int index = Hash {}(key) % num_hash_buckets;
    hash_table_.at(index).push_back(insert_itr);

    return insert_itr;
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::erase(const Key &key)
{
    auto hash_table_itr = find_hash_itr_(key);

    int index = Hash {}(key) % num_hash_buckets;
    if (hash_table_itr == hash_table_.at(index).end())
        return end();

    auto elem_itr = *hash_table_itr;

    data_.remove(elem_itr);
    hash_table_.at(index).remove(hash_table_itr);

    return elem_itr;
}

template <typename Key, typename T, typename Hash>
void hash_table<Key, T, Hash>::rehash_()
{
    if (size() >= num_hash_buckets) {
        clear_hash_table_();

        num_hash_buckets *= 2;
        hash_table_.resize(num_hash_buckets);
        for (auto elem_itr = data_.begin(), elem_end_itr = data_.end(); elem_itr != elem_end_itr; ++elem_itr) {
            insert_in_hash_table_(elem_itr);
        }
    }
}

template <typename Key, typename T, typename Hash>
void hash_table<Key, T, Hash>::insert_in_hash_table_(const list_itr_t &elem_itr)
{
    Key key = elem_itr->first;
    int index = Hash {}(key) % num_hash_buckets;
    hash_table_.at(index).push_back(elem_itr);
}

template <typename Key, typename T, typename Hash>
void hash_table<Key, T, Hash>::clear_hash_table_()
{
    for (int index = 0; index != num_hash_buckets; ++index) {
        hash_table_.at(index).clear();
    }
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::find(const Key &key) const
{
    int index = Hash {}(key) % num_hash_buckets;
    list<list_itr_t> const &hash_table_nodes = hash_table_.at(index);

    for (auto list_itr : hash_table_nodes) {
        if (list_itr->first == key) {
            return list_itr;
        }
    }

    return data_.end();
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::hash_itr_t hash_table<Key, T, Hash>::find_hash_itr_(const Key &key) const
{
    int index = Hash {}(key) % num_hash_buckets;
    list<list_itr_t> const &hash_table_nodes = hash_table_.at(index);

    auto hash_table_itr = hash_table_nodes.begin();
    auto hash_table_end_itr = hash_table_nodes.end();
    for (; hash_table_itr != hash_table_end_itr; ++hash_table_itr) {
        if ((*hash_table_itr)->first == key) {
            return hash_table_itr;
        }
    }

    return hash_table_itr;
}

template <typename Key, typename T, typename Hash>
size_t hash_table<Key, T, Hash>::size() const
{
    return data_.size();
}

template <typename Key, typename T, typename Hash>
bool hash_table<Key, T, Hash>::empty() const
{
    return data_.size() == 0;
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::begin() const
{
    return data_.begin();
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::end() const
{
    return data_.end();
}

}  // namespace my_containers

#endif
