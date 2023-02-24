#include <gtest/gtest.h>

#include "hash_table.hpp"

int main()
{
    int array[5];

    array[4] = 3;
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
