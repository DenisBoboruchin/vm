#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>

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

    //    bool insert (const Key& key, const T& elem);
    //    T* find (const Key& key) const;

    size_t size() const;
    bool empty() const;

private:
    static constexpr size_t NUM_HASH_BUCKETS = 1024;
    using Pair_key_elem = typename std::pair<Key, T>;

    size_t size_ = 0;
    int last_insert_index = -1;
    std::array<list<Pair_key_elem>, NUM_HASH_BUCKETS> data_ {};
};

/*
template <typename Key, typename T, typename Hash>
bool hash_table<Key, T, Hash>::insert (const Key& key, const T& elem)
{
    int index = Hash {} (key) % NUM_HASH_BUCKETS;
    list<Pair_key_elem>& list_of_pairs = data_.at(index);

    Pair_key_elem new_pair = {index, key};

    if (!list_of_pairs.empty ())
    {
        Pair_key_elem candidate = list_of_pairs.find (new_pair);

        if (candidate == new_pair)
            return 0;
    }

    list_of_pairs.push_front (new_pair);
    size_++;

    return 1;
}
*/

/*
template <typename Key, typename T, typename Hash>
T& hash_table<Key, T, Hash>::find (const Key& key) const
{
    int index = Hash {} (key) % NUM_HASH_BUCKETS;
    list<Pair_key_elem>& list_of_pairs = data_.at(index);

    Pair_key_elem new_pair = {key, elem};

    if (!list_of_pairs.empty ())
    {
        if (lists_of_pairs.get_elem (new_pair)
    }

    return data_.at(last_insert_index).front ();
}
*/

template <typename Key, typename T, typename Hash>
size_t hash_table<Key, T, Hash>::size() const
{
    return size_;
}

template <typename Key, typename T, typename Hash>
bool hash_table<Key, T, Hash>::empty() const
{
    return size_ == 0;
}

}  // namespace my_containers

#endif
