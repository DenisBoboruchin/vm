#include <algorithm>

#include "teachable_dictionary.hpp"

namespace dictionary {
static std::pair<std::string, int> find_min_lev_dist_in_hash_table(
    const my_containers::hash_table<std::string, int> &hash_table, const std::string &word, const int lev_const);

static int calc_lev_dist(const std::string &word1, const std::string &word2, const int lev_const);

teachable_dictionary::teachable_dictionary(const std::string &data_path) : data_dictionary_path_ {data_path}, size_ {0}
{
    if (data_path.empty()) {
        std::cout << "dictionary data is empty" << std::endl;
        return;
    }

    std::ifstream dictionary_data_stream {data_path};
    if (!dictionary_data_stream) {
        std::cout << "incorrect dictionary data PATH: " << data_path << std::endl;
        exit(0);
    }

    int lenth = 0;
    dictionary_data_stream >> lenth;
    if (!lenth) {
        std::cout << "dictionary data file is empty" << std::endl;
    }

    while (!dictionary_data_stream.eof()) {
        std::string word {};
        int freq = 0;
        int num_lenth = 0;

        dictionary_data_stream >> num_lenth;

        dictionary_.insert(lenth, {});
        numeric_hash_table &hash_table = dictionary_.begin()->second;
        for (int index = 0; index != num_lenth; ++index) {
            dictionary_data_stream >> word;
            dictionary_data_stream >> freq;
            hash_table.insert(word, freq);

            size_++;
        }

        dictionary_data_stream >> lenth;
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
        data_save_path << dictionary_elem.first << " " << hash_table.size() << std::endl << std::endl;

        for (auto elem : hash_table) {
            data_save_path << elem.first << " " << elem.second << std::endl;
        }

        data_save_path << std::endl;
    }

    data_save_path.close();
    return 1;
}

bool teachable_dictionary::read_text(const std::string &text_path)
{
    std::ifstream teached_stream(text_path);
    if (!teached_stream) {
        std::cout << "error in reading\n";
        return 0;
    }

    std::string word {};
    for (teached_stream >> word; !teached_stream.eof(); teached_stream >> word) {
        int word_len = word.size();

        auto hash_table_lenth_itr = dictionary_.find(word_len);
        if (hash_table_lenth_itr != dictionary_.end()) {
            numeric_hash_table &hash_table = hash_table_lenth_itr->second;

            auto elem_itr = hash_table.find(word);
            if (elem_itr != hash_table.end()) {
                elem_itr->second = elem_itr->second + 1;
            } else {
                hash_table.insert(word, 1);
                size_++;
            }
        } else {
            dictionary_.insert(word_len, {});
            numeric_hash_table &hash_table = dictionary_.begin()->second;
            hash_table.insert(word, 1);

            size_++;
        }
    }

    teached_stream.close();
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

bool teachable_dictionary::correct_text(const std::string &text_for_correct_path, const int lev_const) const
{
    std::ifstream text_stream {text_for_correct_path};
    if (!text_stream) {
        std::cout << "error reading text to correct from path: " << text_for_correct_path << std::endl;
        return 0;
    }

    const std::string CORRECTED_STR = "_corrected";
    std::string corrected_text_path {text_for_correct_path};
    corrected_text_path.insert(corrected_text_path.begin() + corrected_text_path.find('.'), CORRECTED_STR.begin(),
                               CORRECTED_STR.end());

    std::ofstream corrected_text_stream {corrected_text_path};
    std::string word {};
    for (text_stream >> word; !text_stream.eof(); text_stream >> word) {
        corrected_text_stream << find_min_levenshtein_distance(word, lev_const);
        corrected_text_stream << " ";
    }

    text_stream.close();
    corrected_text_stream.close();
    return 1;
}

std::string teachable_dictionary::find_min_levenshtein_distance(const std::string &word, const int lev_const) const
{
    if (get_freq(word))
        return word;

    int lenth = word.size();

    std::pair<std::string, int> pair_word_with_min_dist = find_pair_word_with_min_dist_(word, lenth, lev_const);
    if (pair_word_with_min_dist.second == 1) {
        return pair_word_with_min_dist.first;
    }

    std::pair<std::string, int> temp_pair = find_pair_word_with_min_dist_(word, lenth - 1, lev_const);
    if (temp_pair.second == 1) {
        return temp_pair.first;
    }

    if (temp_pair.second < pair_word_with_min_dist.second) {
        pair_word_with_min_dist = temp_pair;
    }

    temp_pair = find_pair_word_with_min_dist_(word, lenth + 1, lev_const);
    if (temp_pair.second == 1) {
        return temp_pair.first;
    }

    if (temp_pair.second < pair_word_with_min_dist.second) {
        pair_word_with_min_dist = temp_pair;
    }

    std::cout << "min distance: " << pair_word_with_min_dist.second << std::endl;
    return pair_word_with_min_dist.first;
}

std::pair<std::string, int> teachable_dictionary::find_pair_word_with_min_dist_(const std::string &word,
                                                                                const int lenth,
                                                                                const int lev_const) const
{
    auto hash_table_lenth_itr = dictionary_.find(lenth);
    std::pair<std::string, int> pair_word_with_min_dist {word, lev_const + 1};
    if (hash_table_lenth_itr == dictionary_.end()) {
        return pair_word_with_min_dist;
    }

    pair_word_with_min_dist = find_min_lev_dist_in_hash_table(hash_table_lenth_itr->second, word, lev_const);

    return pair_word_with_min_dist;
}

std::pair<std::string, int> find_min_lev_dist_in_hash_table(
    const my_containers::hash_table<std::string, int> &hash_table, const std::string &word, const int lev_const)
{
    std::pair<std::string, int> pair_word_with_min_dist {word, lev_const + 1};
    for (auto elem : hash_table) {
        int dist = calc_lev_dist(elem.first, word, lev_const);
        std::cout << "from hash: " << elem.first << "; word: " << word << "; dist: " << dist << std::endl;

        if (dist < pair_word_with_min_dist.second) {
            pair_word_with_min_dist.first = elem.first;
            pair_word_with_min_dist.second = dist;
        }
        if (dist == 1) {
            return pair_word_with_min_dist;
        }
    }

    return pair_word_with_min_dist;
}

int calc_lev_dist(const std::string &word1, const std::string &word2, const int lev_const)
{
    int min_len = word1.size();
    int max_len = word2.size();

    const std::string &sword = min_len > max_len ? word2 : word1;
    const std::string &lword = min_len > max_len ? word1 : word2;

    if (min_len > max_len) {
        int temp_len = max_len;
        min_len = max_len;
        max_len = temp_len;
    }

    std::vector<int> curr_row(max_len + 1);
    std::vector<int> prev_row(max_len + 1);
    for (int i = 0; i != max_len + 1; ++i) {
        prev_row[i] = i;
    }

    for (int i = 1; i != min_len + 1; ++i) {
        curr_row[0] = i;
        for (int j = 1; j != max_len + 1; ++j) {
            int up = prev_row[j] + 1;
            int down = curr_row[j - 1] + 1;
            int diag = prev_row[j - 1];

            if (sword[i - 1] != lword[j - 1]) {
                diag += 1;
            }
            curr_row[j] = std::min(std::min(up, down), diag);
        }

        prev_row = curr_row;
    }

    return curr_row[max_len];
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
