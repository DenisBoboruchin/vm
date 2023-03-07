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

    ASSERT_EQ(first_table.find(4), first_table.end());

    first_table.insert(1, 10);

    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find(4), first_table.end());
    ASSERT_EQ(first_table.find(1), first_table.begin());

    first_table.insert(2, 20);
    ASSERT_EQ(first_table.size(), 2);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find(4), first_table.end());
    ASSERT_EQ(first_table.find(2), first_table.begin());
    
    first_table.insert(3, 30);
    first_table.insert(4, 40);
    
    auto itr = first_table.find (3);
    ASSERT_EQ(itr->first, 3);
    ASSERT_EQ(itr->second, 30);
}

TEST(hash_table, copy_constr)
{
    hash_table<int, int> table_1;
    table_1.insert (1, 3);
    table_1.insert (2,4);

    hash_table<int, int> table_2 {table_1};

    ASSERT_EQ(table_2.size (), 2);
    ASSERT_EQ(table_2.begin()->first, 2);
}

TEST(hash_table, erase)
{
    hash_table<int, int> table;
    ASSERT_EQ(table.size(), 0);

    table.insert(1, 100);
    ASSERT_EQ(table.size(), 1);

    table.erase(2);
    ASSERT_EQ(table.size(), 1);

    table.erase(1);
    ASSERT_EQ(table.size(), 0);
}

TEST(hash_table, insert)
{
    hash_table<int, int> first_table;

    ASSERT_EQ(first_table.size(), 0);
    ASSERT_EQ(first_table.empty(), 1);

    ASSERT_EQ(first_table.find(4), first_table.end());

    first_table.insert(1, 10);

    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);

    int &value = first_table.find(1)->second;
    ASSERT_EQ(value, 10);

    first_table.insert(1, 20);
    ASSERT_EQ(value, 20);

    ASSERT_EQ(first_table.size(), 1);
    ASSERT_EQ(first_table.empty(), 0);
    ASSERT_EQ(first_table.find(4), first_table.end());
}

TEST(hash_table, resize)
{
    hash_table<int, int> table;

    long int num_elems = 1000000;
    for (int i = 0; i != num_elems; ++i) {
        table.insert(i, 10 * i);
    }

    long int sum = 0;
    for (auto elem : table) {
        sum += elem.second;
    }

    ASSERT_EQ(sum, num_elems * (num_elems - 1) * 5);
}

TEST(hash_table, iterator)
{
    hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 100);

    int sum = 0;
    for (auto elem : table) {
        sum += elem.second;
    }

    ASSERT_EQ(sum, 130);
    ASSERT_EQ(table.begin()->first, 3);
}
