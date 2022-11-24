#include <gtest/gtest.h>

#include "queue.hpp"

using my_containers::queue_list;

int main ()
{
    testing::InitGoogleTest ();
    
    return RUN_ALL_TESTS ();
}

TEST (queue_list, consructor)
{
    queue_list<int> queue;

    queue.push (12);
    queue.push (421);
    queue.push (32);

    ASSERT_EQ (queue.front (), 12);
}
