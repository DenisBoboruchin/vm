#include <algorithm>
#include <tuple>

#include "teachable_dictionary.hpp"
#include "reader.hpp"

namespace dictionary {
static std::tuple<std::string, int, int> find_min_lev_dist_in_hash_table(
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
    //    save_data_binary("df");
}

bool teachable_dictionary::save_data(const std::string &path_to_save) const
{
    std::ofstream data_save_stream {path_to_save};
    if (!data_save_stream) {
        std::cout << "incorrect data_save_path" << std::endl;
        return 0;
    }

    std::string save_data_text;
    for (auto dictionary_elem : dictionary_) {
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
    /*
    FILE* data_save_stream = fopen (path_to_save.c_str(), "wb");
    if (!data_save_stream) {
        std::cout << "incorrect data_save_path" << std::endl;
    //    return 0;
    }

    std::vector<char> data {};
    for (auto dictionary_elem : dictionary_)
    {
        numeric_hash_table &hash_table = dictionary_elem.second;

        for (auto elem : hash_table) {
        }
    }

    data_save_stream.close ();
    */
    return 1;
}

bool teachable_dictionary::read_text(const std::string &text_path)
{
    my_containers::reader reader {text_path};
    if (reader.empty()) {
        std::cout << "error in reading file for teach\n";
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
            }
        } else {
            dictionary_.insert(word_len, {});
            numeric_hash_table &hash_table = dictionary_.begin()->second;
            hash_table.insert(word, 1);

            size_++;
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

bool teachable_dictionary::correct_text(const std::string &text_for_correct_path, const int lev_const) const
{
    my_containers::reader reader {text_for_correct_path};
    if (reader.empty()) {
        std::cout << "error in reading file for teach\n";
        return 0;
    }

    const std::string CORRECTED_STR = "_corrected";
    std::string corrected_text_path {text_for_correct_path};
    corrected_text_path.insert(corrected_text_path.begin() + corrected_text_path.find('.'), CORRECTED_STR.begin(),
                               CORRECTED_STR.end());

    std::ofstream corrected_text_stream {corrected_text_path};

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
    corrected_text_stream.close();
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
        std::tuple<std::string, int, int> tuple_word_with_min_dist =
            find_tuple_word_with_min_dist_(word, lenth_minus_one + index, lev_const);

        int dist = std::get<2>(tuple_word_with_min_dist);
        if ((dist > lev_const) || (dist > min_dist)) {
            continue;
        } else if (dist == min_dist) {
            int freq = std::get<1>(tuple_word_with_min_dist);
            if (freq <= freq_word_with_min_dist) {
                continue;
            }
        }
        word_with_min_dist = std::get<0>(tuple_word_with_min_dist);
        freq_word_with_min_dist = std::get<1>(tuple_word_with_min_dist);
        min_dist = dist;
    }

    if (word_with_min_dist == word) {
        std::cout << "could not find a suitable fix for \"" << word << '"' << std::endl;
    }

    return word_with_min_dist;
}

std::tuple<std::string, int, int> teachable_dictionary::find_tuple_word_with_min_dist_(const std::string &word,
                                                                                       const int lenth,
                                                                                       const int lev_const) const
{
    auto hash_table_lenth_itr = dictionary_.find(lenth);
    if (hash_table_lenth_itr == dictionary_.end()) {
        return {word, 0, lev_const + 1};
    }

    return find_min_lev_dist_in_hash_table(hash_table_lenth_itr->second, word, lev_const);
}

std::tuple<std::string, int, int> find_min_lev_dist_in_hash_table(
    const my_containers::hash_table<std::string, int> &hash_table, const std::string &word, const int lev_const)
{
    std::tuple<std::string, int, int> tuple_word_with_min_dist {word, 0, lev_const + 1};
    for (auto elem : hash_table) {
        int dist = calc_lev_dist(elem.first, word, lev_const);
        int old_dist = std::get<2>(tuple_word_with_min_dist);

        if (dist < old_dist) {
            tuple_word_with_min_dist = {elem.first, elem.second, dist};
        } else if ((dist == old_dist) && (elem.second > std::get<1>(tuple_word_with_min_dist))) {
            tuple_word_with_min_dist = {elem.first, elem.second, dist};
        }
    }

    return tuple_word_with_min_dist;
}

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

size_t teachable_dictionary::size() const
{
    return size_;
}

bool teachable_dictionary::empty() const
{
    return size_ == 0;
}

}  // namespace dictionary
