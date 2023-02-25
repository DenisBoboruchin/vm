#include <iostream>

#include <gtest/gtest.h>

#include "list.hpp"

using my_containers::list;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(list, front)
{
    list<int> list;

    list.push_back(12);
    list.push_back(421);
    list.push_back(32);

    ASSERT_EQ(list.front(), 12);
}

TEST(list, back)
{
    list<int> list;

    list.push_back(62);
    list.push_back(41);
    list.push_back(35);

    ASSERT_EQ(list.back(), 35);
}

TEST(list, find)
{
    list<int> list;

    list.push_back(62);
    list.push_back(41);
    list.push_back(35);
    list.push_back(87);

    ASSERT_EQ(list.find(35), 1);

    list.pop_back();

    ASSERT_EQ(list.front(), 62);
    ASSERT_EQ(list.back(), 35);
}

TEST(list, remove)
{
    list<int> list;

    list.push_back(62);
    list.push_back(41);
    list.push_back(35);
    list.push_back(87);

    list.pop_back();

    ASSERT_EQ(list.front(), 62);
    ASSERT_EQ(list.back(), 35);

    ASSERT_EQ(list.remove(41), 1);
    ASSERT_EQ(list.front(), 62);
    ASSERT_EQ(list.back(), 35);
    ASSERT_EQ(list.size(), 2);

    ASSERT_EQ(list.remove(62), 1);
    ASSERT_EQ(list.front(), 35);
    ASSERT_EQ(list.back(), 35);
    ASSERT_EQ(list.size(), 1);
}

TEST(list, size_empty)
{
    list<int> list;

    ASSERT_EQ(list.empty(), true);
    ASSERT_EQ(list.size(), 0);

    list.push_back(62);
    list.push_back(41);
    ASSERT_EQ(list.size(), 2);

    list.push_back(35);
    ASSERT_EQ(list.size(), 3);
}

TEST(list, push_pop_back)
{
    list<int> list;
    list.pop_back();

    list.push_back(2);
    list.push_front(1);
    list.push_back(3);
    list.push_front(0);

    ASSERT_EQ(list.back(), 3);
    ASSERT_EQ(list.front(), 0);

    list.pop_back();
    ASSERT_EQ(list.size(), 3);
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.front(), 0);

    list.push_front(10);
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.front(), 10);
}

TEST(list, push_pop_front)
{
    list<int> list;
    list.pop_front();

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);

    ASSERT_EQ(list.back(), 3);
    ASSERT_EQ(list.front(), 0);

    list.pop_front();
    ASSERT_EQ(list.back(), 3);
    ASSERT_EQ(list.front(), 1);

    list.push_back(4);
    ASSERT_EQ(list.back(), 4);
    ASSERT_EQ(list.front(), 1);
}

TEST(list, copy_constructor)
{
    list<int> list1;

    list1.push_back(62);
    list1.push_back(41);
    list1.push_back(35);

    ASSERT_EQ(list1.back(), 35);
    ASSERT_EQ(list1.front(), 62);

    list<int> list2 {list1};

    ASSERT_EQ(list2.size(), 3);
    ASSERT_EQ(list2.back(), 35);
    ASSERT_EQ(list2.front(), 62);

    list2.pop_front();
    ASSERT_EQ(list2.back(), 35);
    ASSERT_EQ(list2.front(), 41);
}

TEST(list, move_constructor)
{
    list<int> list1;

    list1.push_back(2);
    list1.push_back(4);
    list1.push_back(5);

    ASSERT_EQ(list1.back(), 5);
    ASSERT_EQ(list1.front(), 2);

    list<int> list2 {std::move(list1)};

    ASSERT_EQ(list2.size(), 3);

    ASSERT_EQ(list2.back(), 5);
    ASSERT_EQ(list2.front(), 2);

    list2.pop_front();
    ASSERT_EQ(list2.back(), 5);
    ASSERT_EQ(list2.front(), 4);
}

TEST(list, copy_assigment)
{
    list<int> list1;

    list1.push_back(62);
    list1.push_back(41);
    list1.push_back(35);

    ASSERT_EQ(list1.back(), 35);
    ASSERT_EQ(list1.front(), 62);

    list<int> list2 {};

    list2 = list1;

    ASSERT_EQ(list2.size(), 3);
    ASSERT_EQ(list2.back(), 35);
    ASSERT_EQ(list2.front(), 62);

    list2.pop_front();
    ASSERT_EQ(list2.back(), 35);
    ASSERT_EQ(list2.front(), 41);
}

TEST(list, move_assigment)
{
    list<int> list1;

    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    ASSERT_EQ(list1.back(), 30);
    ASSERT_EQ(list1.front(), 10);

    list<int> list2 {};

    list2 = std::move(list1);

    ASSERT_EQ(list2.size(), 3);
    ASSERT_EQ(list2.back(), 30);
    ASSERT_EQ(list2.front(), 10);

    list2.pop_front();
    ASSERT_EQ(list2.back(), 30);
    ASSERT_EQ(list2.front(), 20);
}

TEST(list, big_test)
{
    list<int> list;

    long int num = 10000000;
    for (int i = 1; i != num + 1; ++i) {
        list.push_back(i);
    }

    ASSERT_EQ(list.size(), num);
    ASSERT_EQ(list.back(), num);
    ASSERT_EQ(list.front(), 1);

    long int sum = 0;
    while (!list.empty()) {
        sum += list.front();
        sum += list.back();

        list.pop_back();
        list.pop_front();
    }

    ASSERT_EQ(sum, num * (num + 1) / 2);
}

TEST(list, struct_test)
{
    struct S {
        int a, b;
        double d;
        char c;
    };

    list<S> list;

    list.push_back({1, 2, 3.5, 3});

    S t = {10, 20, 44.4, 30};
    list.push_front(t);

    ASSERT_EQ(list.front().a, 10);
    ASSERT_EQ(list.front().d, 44.4);
    ASSERT_EQ(list.back().b, 2);
    ASSERT_EQ(list.back().c, 3);

    list.pop_back();

    ASSERT_EQ(list.front().a, 10);
    ASSERT_EQ(list.front().d, 44.4);
    ASSERT_EQ(list.back().b, 20);
    ASSERT_EQ(list.back().c, 30);
}
