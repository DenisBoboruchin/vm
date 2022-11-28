#include <gtest/gtest.h>

#include "queue.hpp"

using my_containers::Iqueue;
using my_containers::queue_list;
using my_containers::queue_stacks;

int main ()
{
    testing::InitGoogleTest ();

    return RUN_ALL_TESTS();
}

TEST (queue, size_empty)
{
    queue_stacks<int> queue;
    ASSERT_EQ (queue.empty (), true);

    queue.push (13);
    ASSERT_EQ (queue.size (), 1);
    ASSERT_EQ (queue.front (), 13);
    ASSERT_EQ (queue.back (), 13);   
} 

TEST (queue, back_front)
{
    queue_list<int> queue;

    queue.push (1);
    ASSERT_EQ (queue.front (), 1);
    ASSERT_EQ (queue.back (), 1);   
    
    queue.push (2);
    ASSERT_EQ (queue.front (), 1);
    ASSERT_EQ (queue.back (), 2);    

    queue.push (3);
    ASSERT_EQ (queue.front (), 1);
    ASSERT_EQ (queue.back (), 3);    
}

TEST (queue, push_pop)
{
    queue_list<int> queue;
    
    queue.pop ();

    queue.push (1);
    ASSERT_EQ (queue.size (), 1);
    ASSERT_EQ (queue.front (), 1);
    ASSERT_EQ (queue.back (), 1);   
    
    queue.push (2);
    ASSERT_EQ (queue.front (), 1);
    ASSERT_EQ (queue.back (), 2);    
    
    queue.push (3);

    queue.pop ();
    queue.pop ();
    queue.pop ();

    ASSERT_EQ (queue.size (), 0);
    ASSERT_EQ (queue.empty (), true);

    queue.push (20);
    ASSERT_EQ (queue.front (), 20);
    ASSERT_EQ (queue.back (), 20);     
}

TEST (queue, copy_constructor)
{
    queue_list<int> queue1;
    
    queue1.pop ();

    queue1.push (20);
    queue1.push (10);
    ASSERT_EQ (queue1.size (), 2);
    ASSERT_EQ (queue1.front (), 20);
    ASSERT_EQ (queue1.back (), 10);   
    
    queue_list<int> queue2 {queue1};

    ASSERT_EQ (queue2.size (), 2);
    ASSERT_EQ (queue2.front (), 20);
    ASSERT_EQ (queue2.back (), 10);   
}

TEST (queue, move_constructor)
{
    queue_list<int> queue1;
    
    queue1.pop ();

    queue1.push (20);
    queue1.push (10);
    ASSERT_EQ (queue1.size (), 2);
    ASSERT_EQ (queue1.front (), 20);
    ASSERT_EQ (queue1.back (), 10);   
    
    queue_list<int> queue2 {std::move(queue1)};

    ASSERT_EQ (queue2.size (), 2);
    ASSERT_EQ (queue2.front (), 20);
    ASSERT_EQ (queue2.back (), 10);   
}

TEST (queue, copy_assignment)
{
    queue_list<int> queue1;
    
    queue1.pop ();

    queue1.push (20);
    queue1.push (10);
    ASSERT_EQ (queue1.size (), 2);
    ASSERT_EQ (queue1.front (), 20);
    ASSERT_EQ (queue1.back (), 10);   
    
    queue_list<int> queue2 {};
    queue2.push (1221);

    queue2 = queue1;

    ASSERT_EQ (queue2.size (), 2);
    ASSERT_EQ (queue2.front (), 20);
    ASSERT_EQ (queue2.back (), 10);   
}

TEST (queue, move_assignment)
{
    queue_list<int> queue1;
    
    queue1.pop ();

    queue1.push (20);
    queue1.push (10);
    ASSERT_EQ (queue1.size (), 2);
    ASSERT_EQ (queue1.front (), 20);
    ASSERT_EQ (queue1.back (), 10);   
    
    queue_list<int> queue2 {};
    queue2.push (111);
    
    queue2 = std::move(queue1);

    ASSERT_EQ (queue2.size (), 2);
    ASSERT_EQ (queue2.front (), 20);
    ASSERT_EQ (queue2.back (), 10);   
}

TEST (queue, virtual_destructor)
{
    queue_list<int>* ptr = new queue_list<int> {};

    Iqueue<int>* base_ptr = ptr;

    delete base_ptr;
}

