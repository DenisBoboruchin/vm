cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

set(PROJECT_NAME stack)
project(${PROJECT_NAME} LANGUAGES CXX)

set(SOURCE_TEST tests/tests.cpp)
set(SOURCE_LIB src/stack_bool.cpp include/stack.hpp) 

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

option(TESTING "Включить тестирование" ON)

#tests
if (TESTING)
    message ("Include testing")
    find_package (GTest REQUIRED)
    include_directories (${GTEST_INCLUDE_DIRS})

    add_executable (${PROJECT_NAME}_tests ${SOURCE_TEST})

    target_link_libraries (${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main)
    enable_testing ()

    add_dependencies (${PROJECT_NAME}_tests ${PROJECT_NAME})
endif ()

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message (clang-format)
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
    add_custom_target(
        clang_format
        COMMAND clang-format
        #-style=file:${CMAKE_SOURCE_DIR}/.clang-format
        -i
        -dump-config
        ${ALL_SOURCE_FILES}
    )
endif()

#clang-tidy
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message (clang-tidy)
    set(CLANG_TIDY_FLAGS
        clang-tidy
        -format-style=file:${CMAKE_SOURCE_DIR}/.clang-tidy 
        -dump-config
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_FLAGS}")
endif()

#sanitizers
if (ADD_SANITIZERS)
    message ("Build with sanitizers")

    add_compile_options (-fsanitize=address -fsanitize=undefined -g)
    set_target_properties (${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()


