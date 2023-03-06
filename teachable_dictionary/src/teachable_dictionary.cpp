#include "teachable_dictionary.hpp"

namespace dictionary {

teachable_dictionary::teachable_dictionary(const std::string &data_path) : data_dictionary_path_ {data_path}
{
    std::ifstream dictionary_data_stream {data_path};
    if (!dictionary_data_stream) {
        std::cout << "incorrect dictionary data PATH: " << data_path << std::endl;
        exit(0);
    }

    std::string word {};
    int freq = 0;
    for (dictionary_data_stream >> word; !dictionary_data_stream.eof(); dictionary_data_stream >> word) {
        dictionary_data_stream >> freq;
        dictionary_.insert(word, freq);
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

    for (auto itr = dictionary_.begin(), itr_end = dictionary_.end(); itr != itr_end; ++itr) {
        data_save_path << itr->first << " " << itr->second << std::endl;
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
        auto word_itr = dictionary_.find(word);
        if (word_itr != dictionary_.end()) {
            word_itr->second++;
        } else {
            dictionary_.insert(word, 1);
        }
    }

    teached_stream.close();
    return 1;
}

int teachable_dictionary::get_freq(const std::string &word) const
{
    auto word_itr = dictionary_.find(word);

    if (word_itr == dictionary_.end()) {
        return 0;
    } else {
        return word_itr->second;
    }
}

bool teachable_dictionary::correct_text(const std::string &text_for_correct_path) const
{
    return 1;
}

size_t teachable_dictionary::size() const
{
    return dictionary_.size();
}

bool teachable_dictionary::empty() const
{
    return dictionary_.size() == 0;
}

}  // namespace dictionary
