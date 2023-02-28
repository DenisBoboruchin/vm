#include <gtest/gtest.h>

#include "hash_table.hpp"

using my_containers::hash_table;
using my_containers::pair_wrapper;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(pair_wrapper, equal)
{
    pair_wrapper<std::string, int> p1 {{"apple", 5}};
    pair_wrapper<std::string, int> p2 {{"apple", 7}};
    pair_wrapper<std::string, int> p3 {{"orange", 5}};

    ASSERT_EQ(p1 == p2, 1);
    ASSERT_EQ(p1 == p3, 0);
    ASSERT_EQ(p2 == p3, 0);
    ASSERT_EQ(p1 == p1, 1);
}

TEST(hash_table, constructors)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);
}

TEST(hash_table, insert)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);

    //    ASSERT_EQ (first_table.insert (1, 3), 1);
    //    ASSERT_EQ (first_table.size (), 1);
}
