#include "include/complex_num.h"

#include <gtest/gtest.h>

int main ()
{
    ::testing::InitGoogleTest();

    //std::cout << complex_num::complex (1, 2) << std::endl;

    return RUN_ALL_TESTS ();
}

TEST (complex, test1)
{
    complex_num::complex a (1, 2);
    complex_num::complex b = a;
    
    ASSERT_TRUE (b == a);
    b = b + 3;
    //b = 2 + b;

    ASSERT_TRUE (b != a);
    ASSERT_TRUE (b > a);
    ASSERT_TRUE (a < b);
    
    ASSERT_EQ (b, complex_num::complex (6, 2));
    
    //a = 1 - b;
    ASSERT_EQ (a, complex_num::complex (-5, -2));
}

TEST (complex, test2)
{
    complex_num::complex a;
    ASSERT_EQ (a, complex_num::complex (0, 0));

    complex_num::complex b (1, -1);
    
    a = a * a;
    ASSERT_EQ (a, complex_num::complex (0, 0));

    ASSERT_EQ (a * b, complex_num::complex (0));
    
    //b = 2 * b;
    ASSERT_EQ (b, complex_num::complex (2, -2));

    a = 4;
    complex_num::complex c = a;
    ASSERT_EQ (c, complex_num::complex (4, 0));
}

TEST (complex, test3)
{
    complex_num::complex a = 3;
    complex_num::complex b (0, 3);
    
    ASSERT_EQ (a + b, complex_num::complex (3, 3));
    ASSERT_EQ (a.abs (), 3);
    
    a = a + b;

    ASSERT_EQ (a / complex_num::complex (1, 1), complex_num::complex (3, 0));

    ASSERT_EQ (a, complex_num::complex (3, 3));
}

