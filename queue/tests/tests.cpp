#include <gtest/gtest.h>

#include "queue.hpp"

using my_containers::Iqueue;
using my_containers::queue_list;
using my_containers::queue_stacks;

template <typename queueType>
class queue_test : public testing::Test {
};

using queue_types = ::testing::Types<queue_stacks<int>, queue_list<int>, queue_stacks<bool>, queue_list<bool>>;
TYPED_TEST_SUITE(queue_test, queue_types);

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(queue, queue_bool)
{
    queue_list<bool> queue1;
    queue1.push (true);
    queue1.pop ();

    queue_stacks<bool> queue2;
    queue2.push (true);
    queue2.pop ();
}

TYPED_TEST(queue_test, size_empty)
{
    TypeParam queue;

    ASSERT_EQ(queue.empty(), true);

    queue.push(static_cast<typename TypeParam::Queue_type> (13));
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.front(), static_cast<typename TypeParam::Queue_type> (13));
    ASSERT_EQ(queue.back(), static_cast<typename TypeParam::Queue_type> (13));
}
/*
TYPED_TEST(queue_test, back_front)
{
    TypeParam queue;

    queue.push(1);
    ASSERT_EQ(queue.front(), 1);
    ASSERT_EQ(queue.back(), 1);

    queue.back() = 6;
    ASSERT_EQ(queue.front(), 6);
    ASSERT_EQ(queue.back(), 6);

    queue.back() += 15;
    ASSERT_EQ(queue.back(), 21);

    queue.push(2);
    ASSERT_EQ(queue.back(), 2);

    queue.front() = 5;
    queue.front() += 15;

    ASSERT_EQ(queue.front(), 20);
    ASSERT_EQ(queue.back(), 2);

    queue.push(3);
    ASSERT_EQ(queue.front(), 20);
    ASSERT_EQ(queue.back(), 3);
}

TYPED_TEST(queue_test, push_pop)
{
    TypeParam queue;

    queue.pop();

    queue.push(1);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.front(), 1);
    ASSERT_EQ(queue.back(), 1);

    queue.push(2);
    ASSERT_EQ(queue.front(), 1);
    ASSERT_EQ(queue.back(), 2);

    queue.push(3);
    ASSERT_EQ(queue.front(), 1);
    ASSERT_EQ(queue.back(), 3);

    queue.pop();
    queue.pop();
    queue.pop();

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.empty(), true);

    queue.push(20);
    ASSERT_EQ(queue.front(), 20);
    ASSERT_EQ(queue.back(), 20);
}

TYPED_TEST(queue_test, copy_constructor)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(20);
    queue1.push(15);
    queue1.push(10);
    ASSERT_EQ(queue1.size(), 3);
    ASSERT_EQ(queue1.front(), 20);
    ASSERT_EQ(queue1.back(), 10);

    TypeParam queue2 {queue1};

    ASSERT_EQ(queue2.size(), 3);
    ASSERT_EQ(queue2.front(), 20);
    ASSERT_EQ(queue2.back(), 10);
}

TYPED_TEST(queue_test, move_constructor)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(20);
    queue1.push(10);
    ASSERT_EQ(queue1.size(), 2);
    ASSERT_EQ(queue1.front(), 20);
    ASSERT_EQ(queue1.back(), 10);

    TypeParam queue2 {std::move(queue1)};

    ASSERT_EQ(queue2.size(), 2);
    ASSERT_EQ(queue2.front(), 20);
    ASSERT_EQ(queue2.back(), 10);
}

TYPED_TEST(queue_test, copy_assignment)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(20);
    queue1.push(10);
    ASSERT_EQ(queue1.size(), 2);
    ASSERT_EQ(queue1.front(), 20);
    ASSERT_EQ(queue1.back(), 10);

    TypeParam queue2 {};
    queue2.push(1221);

    queue2 = queue1;

    ASSERT_EQ(queue2.size(), 2);
    ASSERT_EQ(queue2.front(), 20);
    ASSERT_EQ(queue2.back(), 10);
}

TYPED_TEST(queue_test, move_assignment)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(20);
    queue1.push(10);
    ASSERT_EQ(queue1.size(), 2);
    ASSERT_EQ(queue1.front(), 20);
    ASSERT_EQ(queue1.back(), 10);

    queue1.back() += 15;
    ASSERT_EQ(queue1.back(), 25);

    TypeParam queue2 {};
    queue2.push(111);

    queue2 = std::move(queue1);

    ASSERT_EQ(queue2.size(), 2);
    ASSERT_EQ(queue2.front(), 20);
    ASSERT_EQ(queue2.back(), 25);
}

TYPED_TEST(queue_test, struct_test)
{
    struct S {
        int a, b;
        double d;
        char c;
    };

    queue_stacks<S> queue;

    queue.push({1, 2, 3.5, 3});

    S t = {10, 20, 44.4, 30};
    queue.push(t);

    ASSERT_EQ(queue.back().a, 10);
    ASSERT_EQ(queue.back().d, 44.4);
    ASSERT_EQ(queue.front().b, 2);
    ASSERT_EQ(queue.front().c, 3);

    queue.pop();

    ASSERT_EQ(queue.front().a, 10);
    ASSERT_EQ(queue.front().d, 44.4);
    ASSERT_EQ(queue.back().b, 20);
    ASSERT_EQ(queue.back().c, 30);
}

TYPED_TEST(queue_test, big_test)
{
    TypeParam queue;

    int num_elems = 10000000;
    for (int count = 0; count != num_elems; ++count)
        queue.push(count);

    long sum = 0;
    while (!queue.empty()) {
        sum += queue.front();
        queue.pop();
    }

    ASSERT_EQ(sum, static_cast<long>(num_elems) * (num_elems - 1) / 2);
}*/
