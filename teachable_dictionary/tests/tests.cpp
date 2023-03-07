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
    teachable_dictionary dictionary(std::string(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt")));
    ASSERT_EQ(dictionary.empty(), 0);

    teachable_dictionary empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.empty(), 1);
}

TEST(teachable_dictionary, read_text)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    int freq = dictionary.get_freq("apple");
    ASSERT_EQ(freq, 1);

    int prev_size = dictionary.size();

    ASSERT_EQ(dictionary.empty(), 0);
    dictionary.read_text(PROJECT_DIR_PATH + std::string("/tests/data_base/teacher.txt"));
    ASSERT_EQ(dictionary.size(), prev_size);
}
