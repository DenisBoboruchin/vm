#include <gtest/gtest.h>

#include "reader.hpp"

using my_containers::reader;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(reader, constr)
{
    reader rdr {PROJECT_DIR_PATH + std::string("/reader/tests/text.txt")};

    std::cout << rdr.check_punct();
    std::cout << rdr.get_word();
    std::cout << rdr.check_punct();
    std::cout << rdr.get_word();
    std::cout << rdr.check_punct() << std::endl;
}
