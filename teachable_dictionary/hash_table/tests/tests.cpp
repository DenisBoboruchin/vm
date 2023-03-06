#include <gtest/gtest.h>

#include "hash_table.hpp"

using my_containers::hash_table;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(hash_table, constructors)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);
}

TEST(hash_table, find)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);

    ASSERT_EQ(first_table.find (4), first_table.end ());

    first_table.insert (1, 10);
    
    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find (4), first_table.end ());
    ASSERT_EQ(first_table.find (1), first_table.begin ());

    first_table.insert (2, 20);
    ASSERT_EQ(first_table.size(), 2);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find (4), first_table.end ());
    ASSERT_EQ(first_table.find (2), first_table.begin ());
}

TEST(hash_table, insert)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);

    ASSERT_EQ(first_table.find (4), first_table.end ());

    first_table.insert (1, 10);
    
    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);

    int& value = first_table.find (1)->second;
    ASSERT_EQ(value, 10);

    first_table.insert (1, 20); 
    ASSERT_EQ(value, 20);

    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find (4), first_table.end ());
}


