#include <algorithm>
#include <cstring>
#include <sstream>
#include <thread>
#include <future>

#include "teachable_dictionary.hpp"
#include "work_with_bytes.hpp"

namespace dictionary {

struct word_freq_dist_t final {
    std::string word {};
    int freq = 0;
    int dist = 0;
};

namespace {

int calc_lev_dist(const std::string &word1, const std::string &word2, const int lev_const)
{
    int min_len = word1.size();
    int max_len = word2.size();

    const std::string &sword = min_len > max_len ? word2 : word1;
    const std::string &lword = min_len > max_len ? word1 : word2;

    if (min_len > max_len) {
        int temp_len = min_len;
        min_len = max_len;
        max_len = temp_len;
    }

    std::vector<int> curr_row(min_len + 1);
    std::vector<int> prev_row(min_len + 1);
    for (int i = 0; i != min_len + 1; ++i) {
        prev_row[i] = i;
    }

    for (int i = 1; i != max_len + 1; ++i) {
        curr_row[0] = i;
        for (int j = 1; j != min_len + 1; ++j) {
            int up = prev_row[j] + 1;
            int down = curr_row[j - 1] + 1;
            int diag = prev_row[j - 1];

            if (sword[j - 1] != lword[i - 1]) {
                diag += 1;
            }
            curr_row[j] = std::min(std::min(up, down), diag);
        }
        prev_row = curr_row;
    }

    return curr_row[min_len];
}

word_freq_dist_t find_min_lev_dist_in_hash_table(const my_containers::hash_table<std::string, int> &hash_table,
                                                 const std::string &word, const int lev_const)
{
    word_freq_dist_t word_freq_dist {word, 0, lev_const + 1};
    for (auto elem : hash_table) {
        int dist = calc_lev_dist(elem.first, word, lev_const);
        int old_dist = word_freq_dist.dist;

        if (dist < old_dist) {
            word_freq_dist = {elem.first, elem.second, dist};
        } else if ((dist == old_dist) && (elem.second > word_freq_dist.freq)) {
            word_freq_dist = {elem.first, elem.second, dist};
        }
    }

    return word_freq_dist;
}

std::string add_extension(const std::string &str, const std::string &ext)
{
    std::string res {str};

    size_t offset = res.find('.');
    if (offset == std::string::npos) {
        res.append(ext);
    } else {
        res.replace(res.begin() + offset, res.end(), ext.begin(), ext.end());
    }

    return res;
}

std::vector<std::string> get_words(work_with_bytes::reader &reader)
{
    std::vector<std::string> words_base {};
    std::string word = reader.get_word();
    while (word.size()) {
        words_base.push_back(word);
        reader.get_punct();

        word = reader.get_word();
    }

    return words_base;
}

}  // namespace

teachable_dictionary::teachable_dictionary(const std::string &data_path, const bool read_bytes)
    : data_dictionary_path_ {data_path}, size_ {0}, size_data_in_bytes_ {0}
{
    if (data_path.empty()) {
        std::cout << "dictionary data is empty" << std::endl;
        return;
    }

    if (read_bytes) {
        std::cout << "read data from binary file: " << data_path << std::endl;
        create_data_from_bytes_(data_path);
        return;
    }

    std::ifstream dictionary_data_stream {data_path};
    if (!dictionary_data_stream) {
        std::cout << "empty dictionary data PATH: " << data_path << std::endl;
        return;
    }

    std::stringstream text_string {};
    text_string << dictionary_data_stream.rdbuf();
    dictionary_data_stream.close();

    int lenth = 0;
    text_string >> lenth;
    if (!lenth) {
        std::cout << "dictionary data file is empty" << std::endl;
        return;
    }

    while (!text_string.eof()) {
        std::string word {};
        int freq = 0;
        int num_lenth = 0;

        text_string >> num_lenth;

        dictionary_.insert(lenth, {});
        numeric_hash_table &hash_table = dictionary_.begin()->second;
        for (int index = 0; index != num_lenth; ++index) {
            text_string >> word;
            text_string >> freq;
            hash_table.insert(word, freq);

            size_data_in_bytes_ += word.size() + 1;  // num bytes in word
            size_data_in_bytes_ += sizeof(int);      // bytes for frequency
            size_++;
        }

        text_string >> lenth;
        size_data_in_bytes_ += 2 * sizeof(int);  // bytes for lenth words and num word with this lenth
    }
}

void teachable_dictionary::create_data_from_bytes_(const std::string &data_path)
{
    work_with_bytes::reader reader {data_path};
    while (!reader.can_get_int()) {
        int lenth = reader.get_int();
        int num_lenth = reader.get_int();
        dictionary_.insert(lenth, {});

        numeric_hash_table &hash_table = dictionary_.begin()->second;
        for (int index = 0; index != num_lenth; ++index) {
            std::string word = reader.get_word();
            int freq = reader.get_int();
            hash_table.insert(word, freq);
            size_++;
        }
    }
    size_data_in_bytes_ = reader.size();
}

teachable_dictionary::~teachable_dictionary()
{
    if (size_) {
        save_data(data_dictionary_path_);
        save_data_binary(data_dictionary_path_);
    }
}

bool teachable_dictionary::save_data(const std::string &path_to_save) const
{
    if (!path_to_save.size()) {
        return 0;
    }
    std::string path_to_save_ex = add_extension(path_to_save, ".txt");

    std::ofstream data_save_stream {path_to_save_ex};
    if (!data_save_stream) {
        std::cout << "incorrect data_save_path" << std::endl;
        return 0;
    }

    std::cout << "saving in " << path_to_save_ex << std::endl;

    std::string save_data_text;
    for (auto &&dictionary_elem : dictionary_) {
        save_data_text.append(std::to_string(dictionary_elem.first));
        save_data_text.append(1, ' ');

        numeric_hash_table &hash_table = dictionary_elem.second;
        save_data_text.append(std::to_string(hash_table.size()));
        save_data_text.append(1, '\n');

        for (auto elem : hash_table) {
            save_data_text.append(elem.first);
            save_data_text.append(1, ' ');
            save_data_text.append(std::to_string(elem.second));
            save_data_text.append(1, '\n');
        }

        save_data_text.append(1, '\n');
    }

    data_save_stream << save_data_text;
    data_save_stream.close();
    return 1;
}

bool teachable_dictionary::save_data_binary(const std::string &path_to_save) const
{
    if (!path_to_save.size()) {
        return 0;
    }

    std::string path_to_save_ex = add_extension(path_to_save, ".bt");
    FILE *data_save_stream = fopen(path_to_save_ex.c_str(), "wb");
    if (!data_save_stream) {
        std::cout << "incorrect data_byte_save_path" << std::endl;
        return 0;
    }

    std::cout << "saving binary in " << path_to_save_ex << std::endl;

    char *dictionary_data_ptr = new char[size_data_in_bytes_];
    char *pointer = dictionary_data_ptr;
    for (auto &&dictionary_elem : dictionary_) {
        numeric_hash_table &hash_table = dictionary_elem.second;

        int word_len = dictionary_elem.first;
        memcpy(pointer, &word_len, sizeof(int));
        pointer += sizeof(int);

        int num_lenth = hash_table.size();
        memcpy(pointer, &num_lenth, sizeof(int));
        pointer += sizeof(int);

        for (auto elem : hash_table) {
            const std::string &word = elem.first;
            for (int index = 0; index != word_len; ++index) {
                *pointer = word[index];
                pointer++;
            }
            *pointer = '\0';
            pointer++;

            int freq = elem.second;
            memcpy(pointer, &freq, sizeof(int));
            pointer += sizeof(int);
        }
    }

    int num_writed = fwrite(dictionary_data_ptr, sizeof(char), size_data_in_bytes_, data_save_stream);
    if (num_writed != size_data_in_bytes_) {
        std::cout << "error saving in bytecode: saved " << num_writed << ", expected " << size_data_in_bytes_
                  << std::endl;
    }

    delete[] dictionary_data_ptr;
    fclose(data_save_stream);
    return 1;
}

bool teachable_dictionary::read_text(const std::string &text_path)
{
    work_with_bytes::reader reader {text_path};
    if (reader.empty()) {
        std::cout << "error reading file for teach\n";
        return 0;
    }

    reader.get_punct();
    std::string word = reader.get_word();
    int word_len = word.size();
    while (word_len) {
        auto hash_table_lenth_itr = dictionary_.find(word_len);
        if (hash_table_lenth_itr != dictionary_.end()) {
            numeric_hash_table &hash_table = hash_table_lenth_itr->second;

            auto elem_itr = hash_table.find(word);
            if (elem_itr != hash_table.end()) {
                elem_itr->second = elem_itr->second + 1;
            } else {
                hash_table.insert(word, 1);
                size_++;
                size_data_in_bytes_ += word_len + 1;
            }
        } else {
            dictionary_.insert(word_len, {});
            numeric_hash_table &hash_table = dictionary_.begin()->second;
            hash_table.insert(word, 1);

            size_++;
            size_data_in_bytes_ += word_len + 1;
            size_data_in_bytes_ += 2;
        }

        reader.get_punct();
        word = reader.get_word();
        word_len = word.size();
    }

    return 1;
}

int teachable_dictionary::get_freq(const std::string &word) const
{
    int word_len = word.size();
    auto hash_table_lenth_itr = dictionary_.find(word_len);
    if (hash_table_lenth_itr == dictionary_.end())
        return 0;

    numeric_hash_table &hash_table = hash_table_lenth_itr->second;

    auto elem_itr = hash_table.find(word);
    if (elem_itr == hash_table.end()) {
        return 0;
    } else {
        return elem_itr->second;
    }
}

bool teachable_dictionary::correct_text(const std::string &text_for_correct_path, const bool is_multithread,
                                        const int lev_const) const
{
    work_with_bytes::reader reader {text_for_correct_path};
    if (reader.empty()) {
        std::cout << "error in reading file for teach\n";
        return 0;
    }

    const std::string CORRECTED_STR = "_corrected";
    std::string corrected_text_path {text_for_correct_path};
    corrected_text_path.insert(corrected_text_path.begin() + corrected_text_path.find('.'), CORRECTED_STR.begin(),
                               CORRECTED_STR.end());

    std::ofstream corrected_text_stream {corrected_text_path};

    if (!is_multithread) {
        std::string text {};
        text.append(reader.get_punct());

        std::string word = reader.get_word();
        while (word.size()) {
            text.append(find_min_levenshtein_distance(word, lev_const));
            text.append(reader.get_punct());

            word = reader.get_word();
        }
        text.append(reader.get_punct());
        corrected_text_stream << text;
    } else {
        std::vector<std::string> words_base = get_words(reader);
        using vector_itr = typename std::vector<std::string>::iterator;

        auto thread_work = [this](vector_itr start, vector_itr end) {
            std::string corrected_words {};
            for (vector_itr index = start; index != end; ++index) {
                corrected_words.append(find_min_levenshtein_distance(*index));
                corrected_words.append(" ");
            }

            return corrected_words;
        };

        int num_threads = std::thread::hardware_concurrency();
        int num_words_in_bucket = words_base.size() / num_threads;
#if 1
        std::vector<std::future<std::string>> threads_vector;
        for (int index = 0; index != num_threads - 1; ++index) {
            threads_vector.push_back(std::async(std::launch::async, thread_work,
                                                words_base.begin() + index * num_words_in_bucket,
                                                words_base.begin() + (index + 1) * num_words_in_bucket));
        }

        threads_vector.push_back(std::async(std::launch::async, thread_work,
                                            words_base.begin() + (num_threads - 1) * num_words_in_bucket,
                                            words_base.end()));

        for (int index = 0; index != threads_vector.size(); ++index) {
            auto &thread = threads_vector[index];
            thread.wait();
            auto corrected_words = thread.get();

            corrected_text_stream << corrected_words;
        }
#endif

#if 0
        std::vector<std::thread> threads_vector {};
        for (int index = 0; index != num_threads - 1; ++index)
        {
            std::string corrected_words {};
            threads_vector.emplace_back ({thread_work, words_base.begin() + index * num_words_in_bucket, words_base.begin() + (index + 1) * num_words_in_bucket, corrected_words});
        }
        
        std::string corrected_words {};
        threads_vector.emplace_back ({thread_work, words_base.begin() + (num_threads - 1) * num_words_in_bucket, words_base.end(), corrected_words});

        for (int index = 0; index != num_threads; ++index)
        {
            threads_vector[index].join ();
        }
#endif
    }

    corrected_text_stream.close();

    std::cout << "corrected text path: " << corrected_text_path << std::endl;
    return 1;
}

std::string teachable_dictionary::find_min_levenshtein_distance(const std::string &word, const int lev_const) const
{
    if (get_freq(word)) {
        return word;
    }

    int lenth_minus_one = word.size() - 1;
    std::string word_with_min_dist {word};
    int freq_word_with_min_dist = 0;
    int min_dist = lev_const + 1;

    for (int index = 0; index != 3; ++index) {
        word_freq_dist_t word_freq_dist = find_word_freq_dist_(word, lenth_minus_one + index, lev_const);

        int dist = word_freq_dist.dist;
        if ((dist > lev_const) || (dist > min_dist)) {
            continue;
        } else if (dist == min_dist) {
            int freq = word_freq_dist.freq;
            if (freq <= freq_word_with_min_dist) {
                continue;
            }
        }
        word_with_min_dist = word_freq_dist.word;
        freq_word_with_min_dist = word_freq_dist.freq;
        min_dist = dist;
    }

    if (word_with_min_dist == word) {
        std::cout << "could not find a suitable fix for \"" << word << '"' << std::endl;
    }

    return word_with_min_dist;
}

word_freq_dist_t teachable_dictionary::find_word_freq_dist_(const std::string &word, const int lenth,
                                                            const int lev_const) const
{
    auto hash_table_lenth_itr = dictionary_.find(lenth);
    if (hash_table_lenth_itr == dictionary_.end()) {
        return {word, 0, lev_const + 1};
    }

    return find_min_lev_dist_in_hash_table(hash_table_lenth_itr->second, word, lev_const);
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
