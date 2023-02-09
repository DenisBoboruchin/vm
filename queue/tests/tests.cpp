#include <gtest/gtest.h>

#include "queue.hpp"

using my_containers::Iqueue;
using my_containers::queue_list;
using my_containers::queue_stacks;

template <typename Queue_type>
struct queue_test : public testing::Test {
    using Val_t = typename Queue_type::Queue_val_type;

    static constexpr int NUM_VALUES = 8;
    std::array<Val_t, NUM_VALUES> values {static_cast<Val_t> (13), static_cast<Val_t> (1), static_cast<Val_t> (5), static_cast<Val_t> (6),
                                            static_cast<Val_t> (11), static_cast<Val_t> (13.4), static_cast<Val_t> (22.6), static_cast<Val_t> (18)};
};

using queue_types = ::testing::Types<queue_stacks<int>, queue_list<int>, queue_stacks<bool>, queue_list<bool>>;
TYPED_TEST_SUITE(queue_test, queue_types);

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TYPED_TEST(queue_test, size_empty)
{
    TypeParam queue;

    ASSERT_EQ(queue.empty(), true);

    queue.push(this->values[0]);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.front(), this->values[0]);
    ASSERT_EQ(queue.back(), this->values[0]);
}

TYPED_TEST(queue_test, back_front)
{
    TypeParam queue;

    queue.push(this->values[0]);
    ASSERT_EQ(queue.front(), this->values[0]);
    ASSERT_EQ(queue.back(), this->values[0]);

    queue.push(this->values[5]);
    ASSERT_EQ(queue.front(), this->values[0]);
    ASSERT_EQ(queue.back(), this->values[5]);
}

TYPED_TEST(queue_test, push_pop)
{
    TypeParam queue;

    queue.pop();

    queue.push(this->values[0]);
    ASSERT_EQ(queue.size(), 1);
    ASSERT_EQ(queue.front(), this->values[0]);
    ASSERT_EQ(queue.back(), this->values[0]);

    queue.push(this->values[1]);
    ASSERT_EQ(queue.front(), this->values[0]);
    ASSERT_EQ(queue.back(), this->values[1]);

    queue.pop();
    queue.pop();

    ASSERT_EQ(queue.size(), 0);
    ASSERT_EQ(queue.empty(), true);

    queue.push(this->values[2]);
    ASSERT_EQ(queue.front(), this->values[2]);
    ASSERT_EQ(queue.back(), this->values[2]);
}

TYPED_TEST(queue_test, copy_constructor)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(this->values[0]);
    queue1.push(this->values[2]);
    queue1.push(this->values[4]);
    ASSERT_EQ(queue1.size(), 3);
    ASSERT_EQ(queue1.front(), this->values[0]);
    ASSERT_EQ(queue1.back(), this->values[4]);

    TypeParam queue2 {queue1};

    ASSERT_EQ(queue2.size(), 3);
    ASSERT_EQ(queue2.front(), this->values[0]);
    ASSERT_EQ(queue2.back(), this->values[4]);
}

TYPED_TEST(queue_test, move_constructor)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(this->values[0]);
    queue1.push(this->values[2]);
    queue1.push(this->values[4]);
    ASSERT_EQ(queue1.size(), 3);
    ASSERT_EQ(queue1.front(), this->values[0]);
    ASSERT_EQ(queue1.back(), this->values[4]);

    TypeParam queue2 {std::move(queue1)};

    ASSERT_EQ(queue2.size(), 3);
    ASSERT_EQ(queue2.front(), this->values[0]);
    ASSERT_EQ(queue2.back(), this->values[4]);
}

TYPED_TEST(queue_test, copy_assignment)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(this->values[0]);
    queue1.push(this->values[2]);
    queue1.push(this->values[4]);
    ASSERT_EQ(queue1.size(), 3);
    ASSERT_EQ(queue1.front(), this->values[0]);
    ASSERT_EQ(queue1.back(), this->values[4]);

    TypeParam queue2 {};
    queue2.push(this->values[1]);

    queue2 = queue1;

    ASSERT_EQ(queue2.size(), 3);
    ASSERT_EQ(queue2.front(), this->values[0]);
    ASSERT_EQ(queue2.back(), this->values[4]);
}

TYPED_TEST(queue_test, move_assignment)
{
    TypeParam queue1;

    queue1.pop();

    queue1.push(this->values[0]);
    queue1.push(this->values[4]);
    queue1.push(this->values[2]);
    ASSERT_EQ(queue1.size(), 3);
    ASSERT_EQ(queue1.front(), this->values[0]);
    ASSERT_EQ(queue1.back(), this->values[2]);

    TypeParam queue2 {};
    queue2.push(this->values[6]);

    queue2 = std::move(queue1);

    ASSERT_EQ(queue2.size(), 3);
    ASSERT_EQ(queue2.front(), this->values[0]);
    ASSERT_EQ(queue2.back(), this->values[2]);
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

    if (std::is_same<bool, typename TestFixture::Val_t>::value)
    { 
        ASSERT_EQ(sum, num_elems - 1);
    }
    else
    {
        ASSERT_EQ(sum, static_cast<long>(num_elems) * (num_elems - 1) / 2);
    }
}

TEST(queue_stacks_test, struct_test)
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

TEST(queue_list_test, struct_test)
{
    struct S {
        int a, b;
        double d;
        char c;
    };

    queue_list<S> queue;

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


