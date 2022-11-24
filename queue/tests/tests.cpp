#include <gtest/gtest.h>

#include "queue.hpp"

using my_containers::queue_list;

int main ()
{
    testing::InitGoogleTest ();
    
    return RUN_ALL_TESTS ();
}

TEST (queue, front)
{
    queue_list<int> queue;

    queue.push (12);
    queue.push (421);
    queue.push (32);

    ASSERT_EQ (queue.front (), 12);
}

TEST (queue, back)
{
    queue_list<int> queue;

    queue.push (62);
    queue.push (41);
    queue.push (35);

    ASSERT_EQ (queue.back (), 35);
}

TEST (queue, size_empty)
{
    queue_list<int> queue;

    ASSERT_EQ (queue.empty (), true);
    ASSERT_EQ (queue.size (), 0);
    
    queue.push (62);
    queue.push (41);
    ASSERT_EQ (queue.size (), 2);

    queue.push (35);
    ASSERT_EQ (queue.size (), 3);
}

TEST (queue, push_pop)
{
    queue_list<int> queue;

    queue.push (1);
    queue.push (2);
    queue.push (3);

    ASSERT_EQ (queue.back (), 3);
    ASSERT_EQ (queue.front (), 1);

    queue.pop ();
    ASSERT_EQ (queue.back (), 3);
    ASSERT_EQ (queue.front (), 2);
    
    queue.push (4);
    ASSERT_EQ (queue.back (), 4);
    ASSERT_EQ (queue.front (), 2);
}

