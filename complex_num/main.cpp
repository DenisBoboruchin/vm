#include "include/complex_num.h"

#include <gtest/gtest.h>

int main ()
{
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS ();
}

TEST (complex, test1)
{
    complex_num::complex a (1, 2);
    complex_num::complex b = -a;
    ASSERT_TRUE (b == -a);
    b = b + 3;

    ASSERT_EQ (b, complex_num::complex (4, -2));
}

TEST (complex, test2)
{
    complex_num::complex a;
    ASSERT_EQ (a, complex_num::complex (0, 0));

    a = a * a;
    ASSERT_EQ (a, complex_num::complex (0, 0));

    a = 4;
    complex_num::complex b = a;
    ASSERT_EQ (b, complex_num::complex (4, 0));
}

TEST (complex, test3)
{
    complex_num::complex a = 3;
    complex_num::complex b (0, 3);
    ASSERT_EQ (a + b, complex_num::complex (3, 3));

    a = a + b;

    ASSERT_EQ (a / complex_num::complex (1, 1), complex_num::complex (3, 0));

    ASSERT_EQ (a, complex_num::complex (3, 3));
}

