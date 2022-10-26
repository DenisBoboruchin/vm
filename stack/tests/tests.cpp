#include <gtest/gtest.h>

#include "stack.hpp"
using my_containers::stack;

int main()
{
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(stack_int, constructors)
{    
    stack<int> stack0 {};
    ASSERT_EQ(stack0.capacity(), stack<int>::MIN_CAPACITY);
    ASSERT_EQ(stack0.size(), 0);

    stack<int> stack2 = stack0;
    ASSERT_EQ(stack2.size(), 0);
    ASSERT_EQ(stack2.capacity(), stack<int>::MIN_CAPACITY);

    stack<int> stack3 = std::move(stack2);
    ASSERT_EQ(stack3.size(), 0);
    ASSERT_EQ(stack3.capacity(), stack<int>::MIN_CAPACITY);
}

TEST(stack_bool, default_constructor)
{
    stack<bool> stack0 {};
    ASSERT_EQ(stack0.capacity(), stack<bool>::MIN_CAPACITY);
    ASSERT_EQ(stack0.size(), 0);
} 

TEST(stack_int, push)
{
    stack<int> stack0;

    stack0.push(-21);
    ASSERT_EQ(stack0.size(), 1);

    for (int i = 0; i < 100; i++)
        stack0.push(i);

    ASSERT_EQ(stack0.size(), 101);
}

TEST(stack_bool, push)
{
    stack<bool> stack0;

    stack0.push(true);
    stack0.push(false);
    ASSERT_EQ(stack0.size(), 2);
}

TEST(stack_int, pop)
{
    stack<int> stack0;

    stack0.push(1);
    stack0.pop();
    ASSERT_EQ(stack0.size(), 0);
}

TEST(stack_bool, pop)
{
    stack<bool> stack0;

    stack0.push(true);
    stack0.push(true);
    stack0.pop();
    ASSERT_EQ(stack0.size(), 1);
}

TEST(stack_int, top)
{
    stack<int> stack0;

    stack0.push(10);
    ASSERT_EQ(stack0.top(), 10);

    stack0.push(20);
    ASSERT_EQ(stack0.top(), 20);

    stack0.pop();
    ASSERT_EQ(stack0.top(), 10);
}

TEST(stack_bool, top)
{
    stack<bool> stack0;

    stack0.push(1);
    stack0.push(1);

    ASSERT_EQ(stack0.top(), true);

    stack0.pop();
    ASSERT_EQ(stack0.size(), 1);
    ASSERT_EQ(stack0.top(), true);
    ASSERT_EQ(stack0.capacity(), stack<bool>::MIN_CAPACITY);

    for (int i = 0; i < 17; i++)
        stack0.push(i % 2);

    ASSERT_EQ(stack0.size(), 18);
    ASSERT_EQ(stack0.top(), false);
    stack0.pop();
    ASSERT_EQ(stack0.top(), true);
    stack0.pop();
    ASSERT_EQ(stack0.top(), false);
    stack0.pop();
    ASSERT_EQ(stack0.top(), true);
    stack0.pop();
    ASSERT_EQ(stack0.top(), false);
    stack0.pop();
}

TEST(stack_int, operators_eq)
{
    stack<int> stack0 {};
    stack<int> stack1;

    stack0.push(13);
    stack1.push(24);
    stack1 = stack0;

    ASSERT_EQ(stack1.top(), 13);
    ASSERT_EQ(stack1.capacity(), stack<int>::MIN_CAPACITY);

    stack1.push(14);
    stack0 = std::move(stack1);
    ASSERT_EQ(stack0.size(), 2);
    ASSERT_EQ(stack0.top(), 14);
}

TEST(stack_int, size)
{
    stack<int> stack0;

    int i = 0;
    for (; i < 10; i++)
        stack0.push(i);

    ASSERT_EQ(stack0.size(), 10);
    stack0.pop();

    ASSERT_EQ(stack0.size(), 9);
}

TEST(stack_int, empty)
{
    stack<int> stack0;
    ASSERT_EQ(stack0.empty(), true);

    stack0.push(132);
    ASSERT_EQ(stack0.empty(), false);

    stack0.push(12);
    ASSERT_EQ(stack0.empty(), false);

    stack0.pop();
    stack0.pop();
    ASSERT_EQ(stack0.empty(), true);
}

TEST(stack_int, resize)
{
    stack<int> stack0 {};
    ASSERT_EQ(stack0.capacity(), stack<int>::MIN_CAPACITY);

    for (int i = 0; i < 16; i++)
        stack0.push(i);

    ASSERT_EQ(stack0.capacity(), stack<int>::MIN_CAPACITY);

    stack0.push(-100);
    ASSERT_EQ(stack0.size(), 17);
    ASSERT_EQ(stack0.capacity(), stack<int>::MIN_CAPACITY);

    for (int i = 0; i < 1000; i++)
        stack0.push(i);

    ASSERT_EQ(stack0.capacity(), 1024);
}

TEST(stack_int, check_big_data)
{
    stack<int> stack {};

    long int num = 10000000;

    for (int i = 1; i < num + 1; i++)
        stack.push(i);

    long int sum = 0;
    for (int i = 1; i < num + 1; i++) {
        sum += stack.top();
        stack.pop();
    }

    ASSERT_EQ(sum, num * (num + 1) / 2);
}

TEST(stack_struct, functional_test)
{
    struct T {
        int a = 0;
        int b = 1;
        double c = 10;
    };

    struct U {
        T t {};
        float a = 1;
    };

    U elem0 {{1, 2, 3}};
    U elem1 {{10, 20, 30}, 2};
    U elem2 {{100, 200, 300}, 3};

    stack<U> stack {};
    stack.push(elem0);
    stack.push(elem1);
    stack.push(elem2);

    U elem3 = stack.top();
    ASSERT_EQ(elem3.a, elem2.a);
    ASSERT_EQ(elem3.t.b, elem2.t.b);
    stack.pop();

    elem3 = stack.top();
    ASSERT_EQ(elem3.a, elem1.a);
    ASSERT_EQ(elem3.t.a, elem1.t.a);
    stack.pop();

    elem3 = stack.top();
    ASSERT_EQ(elem3.a, 1);
    ASSERT_EQ(elem3.t.c, 3);
}
