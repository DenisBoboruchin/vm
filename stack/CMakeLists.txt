cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(stack)

include(FetchContent)

FetchContent_Declare(
    googletest
 
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_INCLUDE_DIR}, include)

set(SOURCE_TEST tests/tests.cpp)
set(SOURCE_LIB src/stack_bool.cpp) 

add_library(stack STATIC ${SOURCE_LIB})
add_executable(test ${SOURCE_TEST})

target_link_libraries(test gtest_main stack)

#add_custom_target(clang-format ALL
#   clang-format -i src/stack_bool.cpp)
