#include <gtest/gtest.h>

#include "teachable_dictionary.hpp"

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(teachable_dictionary, constructor)
{
    teachable_dictionary dictionary(std::string(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt")));

    ASSERT_EQ(dictionary.empty(), 0);
}

TEST(teachable_dictionary, read_text)
{
    teachable_dictionary dictionary(PROJECT_DIR_PATH + std::string("/tests/data_base/data.txt"));

    int prev_freq = dictionary.get_freq("apple");

    ASSERT_EQ(dictionary.empty(), 0);
    dictionary.read_text(PROJECT_DIR_PATH + std::string("/tests/data_base/teacher.txt"));
    ASSERT_EQ(dictionary.get_freq("apple"), prev_freq + 1);
}
