#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <vector>

#include "list.hpp"

namespace my_containers {

template <typename Key, typename T, typename Hash = std::hash<Key>>
class hash_table final {
public:
    hash_table() = default;
    hash_table(const hash_table &other) = default;
    hash_table(hash_table &&other) noexcept = default;

    hash_table &operator=(const hash_table &other) = default;
    hash_table &operator=(hash_table &&other) noexcept = default;

    using hash_table_node_t = typename std::pair<Key, T>;
    using iterator = typename list<hash_table_node_t>::iterator;

    iterator insert(const Key &key, const T &elem);
    iterator erase(const Key& key);
    iterator find(const Key &key) const;
    
    size_t size() const;
    bool empty() const;

    iterator begin() const;
    iterator end() const;

private:
    void rehash_ ();
    size_t num_hash_buckets = 1024;

    list<hash_table_node_t> data_ {};

    using list_itr_t = typename list<hash_table_node_t>::iterator;
    std::vector<list<list_itr_t>> hash_table_ {num_hash_buckets};
};

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::insert(const Key &key, const T &value)
{
    auto elem_itr = find(key);

    if (elem_itr != end()) {
        elem_itr->second = value;
        return elem_itr;
    }

    rehash_ ();

    hash_table_node_t new_elem {key, value};
    data_.push_back(new_elem);

    auto insert_itr = begin();
    int index = Hash {}(key) % num_hash_buckets;
    hash_table_.at(index).push_back(insert_itr);

    return insert_itr;
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::erase(const Key &key)
{
    auto elem_itr = find (key);
    
//   data_.remove (elem_itr);

}

template <typename Key, typename T, typename Hash>
void hash_table<Key, T, Hash>::rehash_ ()
{
    if (size () >= num_hash_buckets)
    {
        num_hash_buckets *= 2;
        
        //hash_table_.clear ();

        for (auto elem : data_)
        {
            insert (elem.first, elem.second);
        }
    }
}

template <typename Key, typename T, typename Hash>
typename hash_table<Key, T, Hash>::iterator hash_table<Key, T, Hash>::find(const Key &key) const
{
    int index = Hash {}(key) % num_hash_buckets;
    list<list_itr_t> hash_table_nodes = hash_table_.at(index);

    for (auto list_itr : hash_table_nodes) {
        if (list_itr->first == key) {
            return list_itr;
        }
    }

    return data_.end();
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
