#include <gtest/gtest.h>

#include "hash_table.hpp"

using my_containers::hash_table;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST (hash_table, constructors)
{
    hash_table<int, int> first_table;
   
    ASSERT_EQ (first_table.size (), 0);
    ASSERT_EQ (first_table.empty (), 1);
}

TEST (hash_table, insert)
{
    hash_table<int, int> first_table;
   
    ASSERT_EQ (first_table.size (), 0);
    ASSERT_EQ (first_table.empty (), 1);

//    ASSERT_EQ (first_table.insert (1, 3), 1);
//    ASSERT_EQ (first_table.size (), 1);
}

