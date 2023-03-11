#ifndef TEACHABLE_DICTIONARY_HPP
#define TEACHABLE_DICTIONARY_HPP

#include <iostream>
#include <fstream>

#include "hash_table.hpp"

namespace dictionary {

class teachable_dictionary final {
public:
    explicit teachable_dictionary(const std::string &data_path = {});
    teachable_dictionary(const teachable_dictionary &other) = default;
    teachable_dictionary(teachable_dictionary &&other) noexcept = default;

    teachable_dictionary &operator=(const teachable_dictionary &other) = default;
    teachable_dictionary &operator=(teachable_dictionary &&other) noexcept = default;

    ~teachable_dictionary();

    size_t size() const;
    bool empty() const;

    int get_freq(const std::string &word) const;

    bool read_text(const std::string &teachable_text);
    bool save_data(const std::string &path_to_save) const;

    bool correct_text(const std::string &text_for_correct_path, const int lev_const = 1) const;
    std::string &find_min_levenshtein_distance(std::string &word, const int lev_const) const;

private:
    std::pair<std::string&, int> find_pair_word_with_min_dist_ (std::string & word, const int lenth, const int lev_const) const;
    using numeric_hash_table = typename my_containers::hash_table<std::string, int>;
    my_containers::hash_table<int, numeric_hash_table> dictionary_;

    std::string data_dictionary_path_;
    int size_;
};

}  // namespace dictionary

#endif
