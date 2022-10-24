cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

set(PROJECT_NAME stack)
project(${PROJECT_NAME} LANGUAGES CXX)

set(SOURCE_TEST tests/tests.cpp)
set(SOURCE_LIB src/stack_bool.cpp include/stack.hpp) 

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB})

#clang-tidy
option(CLANG_TIDY "Include clang-tidy" ON)
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message (clang-tidy " from " ${CMAKE_SOURCE_DIR}/.clang-tidy)
    
    set(CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-format-style=file:${CMAKE_SOURCE_DIR}/.clang-tidy;-checks=*"
    )
endif()
 
option(TESTING "Include testing" ON)
#tests
if (TESTING)
    message ("Include testing")
    find_package (GTest REQUIRED)
    include_directories (${GTEST_INCLUDE_DIRS})

    add_executable (${PROJECT_NAME}_tests ${SOURCE_TEST})

    target_link_libraries (${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main)
    enable_testing ()

    add_custom_target (run_${PROJECT_NAME}_tests 
        COMMENT "Running ${PROJECT_NAME}_tests"
        COMMAND ./${PROJECT_NAME}_tests
    )
    add_dependencies (${PROJECT_NAME}_tests ${PROJECT_NAME})
   
    #sanitizers
    if (ADD_SANITIZERS)
        message ("Build with sanitizers")

        add_compile_options (-fsanitize=address -fsanitize=undefined -g)
        set_target_properties (${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    endif ()
endif ()

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message (clang-format " from " ${CMAKE_SOURCE_DIR}/.clang-format)

    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
    add_custom_target(
        clang_format
        COMMAND clang-format
        -i
        -style=file:${CMAKE_SOURCE_DIR}/.clang-format
        ${ALL_SOURCE_FILES}
    )
endif()

