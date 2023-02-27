#ifndef TEACHABLE_DICTIONARY_HPP
#define TEACHABLE_DICTIONARY_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>

class teachable_dictionary final {
public:
    teachable_dictionary(const std::string &data_path);
    teachable_dictionary(const teachable_dictionary &other) = delete;
    teachable_dictionary(teachable_dictionary &&other) noexcept = delete;

    teachable_dictionary &operator=(const teachable_dictionary &other) = delete;
    teachable_dictionary &operator=(teachable_dictionary &&other) noexcept = delete;

    ~teachable_dictionary();

    size_t size() const;
    bool empty() const;

    bool read_text(const std::string &teachable_text);

private:
    bool save_data_();

    std::fstream dictionary_data_stream_;
    std::unordered_map<std::string, int> dictionary_;
};

#endif
