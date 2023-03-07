#include "teachable_dictionary.hpp"

namespace dictionary {

teachable_dictionary::teachable_dictionary(const std::string &data_path) : data_dictionary_path_ {data_path}, size_ {0}
{
    if (data_path.empty())
    {
        std::cout << "dictionary data is empty" << std::endl;
        return;
    }

    std::ifstream dictionary_data_stream {data_path};
    if (!dictionary_data_stream) {
        std::cout << "incorrect dictionary data PATH: " << data_path << std::endl;
        exit(0);
    }

    std::string word {};
    int freq = 0;
    for (dictionary_data_stream >> word; !dictionary_data_stream.eof(); dictionary_data_stream >> word) {
        dictionary_data_stream >> freq;

        int len_word = word.size();
        auto dictionary_itr = dictionary_.find(len_word);

        if (dictionary_itr == dictionary_.end()) {
            static numeric_hash_table hash_table;
            hash_table.insert(word, freq);

            dictionary_.insert(len_word, hash_table);
            size_++;
        } else {
            dictionary_itr->second.insert(word, freq);
        }
    }

    dictionary_data_stream.close();
}

teachable_dictionary::~teachable_dictionary()
{
    save_data(data_dictionary_path_);
}

bool teachable_dictionary::save_data(const std::string &path_to_save) const
{
    std::ofstream data_save_path {path_to_save};
    if (!data_save_path) {
        std::cout << "incorrect data_save_path" << std::endl;
        return 0;
    }

    for (auto dictionary_elem : dictionary_) {
        numeric_hash_table &hash_table = dictionary_elem.second;

        for (auto elem : hash_table) {
            data_save_path << elem.first << " " << elem.second << std::endl;
        }
    }

    data_save_path.close();
    return 1;
}

bool teachable_dictionary::read_text(const std::string &text_path)
{
    std::ifstream teached_stream(text_path);
    if (!teached_stream) {
        std::cout << "error teacher\n";
        return 0;
    }

    std::string word {};
    for (teached_stream >> word; !teached_stream.eof(); teached_stream >> word) {
        int word_len = word.size();

        auto num_hash_table_itr = dictionary_.find(word_len);
        if (num_hash_table_itr == dictionary_.end()) {
            static numeric_hash_table hash_table;
            hash_table.insert(word, 1);

            dictionary_.insert(word_len, hash_table);
            size_++;
        } else {
            numeric_hash_table &hash_table = num_hash_table_itr->second;
            auto elem_itr = hash_table.find(word);
            if (elem_itr != hash_table.end()) {
                elem_itr->second = elem_itr->second + 1;
            } else {
                hash_table.insert(word, 1);
                size_++;
            }
        }
    }

    teached_stream.close();
    return 1;
}

int teachable_dictionary::get_freq(const std::string &word) const
{
    int word_len = word.size();
    auto num_hash_table_itr = dictionary_.find(word_len);

    numeric_hash_table &hash_table = num_hash_table_itr->second;
    auto elem_itr = hash_table.find(word);

    if (elem_itr == hash_table.end()) {
        return 0;
    } else {
        return elem_itr->second;
    }
}

bool teachable_dictionary::correct_text(const std::string &text_for_correct_path) const
{
    return 1;
}

size_t teachable_dictionary::size() const
{
    return size_;
}

bool teachable_dictionary::empty() const
{
    return size_ == 0;
}

}  // namespace dictionary
