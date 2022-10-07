#include <gtest/gtest.h>

#define private public
#include "stack.h"

using my_containers::stack;

int main ()
{
    ::testing::InitGoogleTest ();

    return RUN_ALL_TESTS ();
}

TEST (stack_int, constructors)
{
    stack<int> stack0;
    ASSERT_EQ (stack0.capacity_, my_containers::MIN_CAPACITY);
    ASSERT_EQ (stack0.size_, 0);

    stack<int> stack1 {32};
    ASSERT_EQ (stack1.size_, 0);
    ASSERT_EQ (stack1.capacity_, 32);
    
    stack<int> stack2 = stack1;
    ASSERT_EQ (stack2.size_, 0);
    ASSERT_EQ (stack2.capacity_, 32);
    ASSERT_TRUE (stack1.data_ != stack2.data_);

    stack<int> stack3 = std::move(stack2);
    ASSERT_EQ (stack3.size_, 0);
    ASSERT_EQ (stack3.capacity_, 32);
}

TEST (stack_bool, default_constructor)
{
    stack<bool> stack0 {8};
    ASSERT_EQ (stack0.capacity_, 8);
    ASSERT_EQ (stack0.size_, 0);
}

TEST (stack_int, push)
{
    stack<int> stack0;
    
    stack0.push (-21);
    ASSERT_EQ (stack0.size_, 1);

    for (int i = 0; i < 100; i++)
        stack0.push (i);

    ASSERT_EQ (stack0.size_, 101);
}

TEST (stack_bool, push)
{
    stack<bool> stack0;
    
    stack0.push (true);
    stack0.push (false);
    ASSERT_EQ (stack0.size_, 2);
}

TEST (stack_int, pop)
{
    stack<int> stack0;
    
    stack0.push (1);
    stack0.pop ();
    ASSERT_EQ (stack0.size_, 0);
}

TEST (stack_bool, pop)
{
    stack<bool> stack0;

    stack0.push (true);
    stack0.push (false);
    stack0.pop ();
    ASSERT_EQ (stack0.size_, 1);
}

TEST (stack_int, top)
{
    stack<int> stack0;
    
    stack0.push (10);
    ASSERT_EQ (stack0.top (), 10);
    
    stack0.push (20);
    ASSERT_EQ (stack0.top (), 20);

    stack0.pop ();
    ASSERT_EQ (stack0.top (), 10);
}

TEST (stack_bool, top)
{
    stack<bool> stack0;

    stack0.push (false);
    stack0.push (true);
    ASSERT_EQ (stack0.top (), true);
    
    stack0.pop ();
    ASSERT_EQ (stack0.size_, 1);
    ASSERT_EQ (stack0.top (), false);

    for (int i = 0; i < 17; i++)
        stack0.push (i % 2);

    ASSERT_EQ (stack0.size_, 18);
    ASSERT_EQ (stack0.top (), false);    
    stack0.pop ();
    ASSERT_EQ (stack0.top (), true);    
    stack0.pop ();
    ASSERT_EQ (stack0.top (), false);    
    stack0.pop ();
    ASSERT_EQ (stack0.top (), true);    
    stack0.pop ();
    ASSERT_EQ (stack0.top (), false);    
    stack0.pop ();
}


TEST (stack_int, operators_eq)
{
    stack<int> stack0 {111};
    stack<int> stack1;

    stack0.push (13);
    stack1.push (24);
    stack1 = stack0;

    ASSERT_EQ (stack1.top (), 13);
    ASSERT_EQ (stack1.capacity_, 111);

    stack1.push (14);
    stack0 = std::move (stack1);
    ASSERT_EQ (stack0.size_, 2);
    ASSERT_EQ (stack0.top (), 14);
}

TEST (stack_int, size)
{
    stack<int> stack0;

    int i = 0;
    for (; i < 10; i++)
        stack0.push (i);
    
    ASSERT_EQ (stack0.size (), 10);
    stack0.pop ();

    ASSERT_EQ (stack0.size (), 9);
}

TEST (stack_int, empty)
{
    stack<int> stack0;
    ASSERT_EQ (stack0.empty (), true);

    stack0.push (132);
    ASSERT_EQ (stack0.empty (), false);
    
    stack0.push (12);
    ASSERT_EQ (stack0.empty (), false);

    stack0.pop ();
    stack0.pop ();
    ASSERT_EQ (stack0.empty (), true);
}

TEST (stack_int, resize)
{
    stack<int> stack0{16};
    ASSERT_EQ (stack0.capacity_, 16);

    for (int i = 0; i < 16; i++)
        stack0.push (i);
    
    ASSERT_EQ (stack0.capacity_, 16);

    stack0.push (-100);
    ASSERT_EQ (stack0.size_, 17);
    ASSERT_EQ (stack0.capacity_, 32);

    for (int i = 0; i < 100; i++)
        stack0.push (i);

    ASSERT_EQ (stack0.capacity_, 128);
}
