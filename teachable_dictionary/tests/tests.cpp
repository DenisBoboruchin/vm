#include <gtest/gtest.h>

#include "teachable_dictionary.hpp"

using dictionary::teachable_dictionary;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(teachable_dictionary, constructor)
{
    teachable_dictionary empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.empty(), 1);
}

TEST(teachable_dictionary, read_text)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    int freq = dictionary.get_freq("checkcorrectonapple");
    ASSERT_EQ(freq, 1);

    int prev_size = dictionary.size();
    dictionary.read_text(PROJECT_DIR_PATH + std::string("/tests/data_base/teacher.txt"));
    ASSERT_EQ(prev_size, dictionary.size());
}

TEST(teachable_dictionary, correct_text)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    dictionary.correct_text(PROJECT_DIR_PATH + std::string("/tests/data_base/text_with_errors.txt"));
}

TEST(teachable_dictionary, multithread_correct_text)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    dictionary.correct_text(PROJECT_DIR_PATH + std::string("/tests/data_base/text_with_errors_multithread.txt"), true);
}

TEST(teachable_dictionary, save_data_binary)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    dictionary.save_data_binary(PROJECT_DIR_PATH + std::string("/tests/data_base/data3.bt"));
}

TEST(teachable_dictionary, read_data_from_binary)
{
    teachable_dictionary dictionary1(PROJECT_DIR_PATH + std::string("/tests/data_base/data3.bt"), false);
    teachable_dictionary dictionary2(PROJECT_DIR_PATH + std::string("/tests/data_base/data3.bt"), true);
}
