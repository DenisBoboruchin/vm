#include "teachable_dictionary.hpp"

teachable_dictionary::teachable_dictionary(const std::string &data_path)
{
    dictionary_data_stream_.open(data_path, dictionary_data_stream_.in | dictionary_data_stream_.out);
    if (!dictionary_data_stream_) {
        std::cout << "incorrect dictionary data PATH: " << data_path << std::endl;
        exit(0);
    }

    std::string word {};
    int freq = 0;
    for (dictionary_data_stream_ >> word; !dictionary_data_stream_.eof(); dictionary_data_stream_ >> word) {
        dictionary_data_stream_ >> freq;
        dictionary_.insert({word, freq});
    }

    dictionary_data_stream_.seekp(0);
}

teachable_dictionary::~teachable_dictionary()
{
    std::string word {};
    dictionary_data_stream_ >> word;
    std::cout << word << std::endl;

    save_data_();
    dictionary_data_stream_.close();
}

bool teachable_dictionary::save_data_()
{
    for (auto itr = dictionary_.begin(), itr_end = dictionary_.end(); itr != itr_end; ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
        dictionary_data_stream_ << itr->first << " " << itr->second << std::endl;
    }

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
            std::cout << "increase " << word << std::endl;
            word_itr->second++;
        } else {
            std::cout << "insert " << word << std::endl;
            dictionary_.insert({word, 1});
        }
    }

    teached_stream.close();
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
