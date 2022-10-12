cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

set(PROJECT_NAME stack)
project(${PROJECT_NAME} LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    googletest
 
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_INCLUDE_DIR}, include)

set(SOURCE_TEST tests/tests.cpp)
set(SOURCE_LIB src/stack_bool.cpp) 

set(ALL_SOURCE_FILES ${SOURCE_TEST} ${SOURCE_LIB})

set(INC_DIR include)


add_compile_options(-fsanitize=address -fsanitize=undefined)

add_library(stack STATIC ${SOURCE_LIB})
add_executable(test ${SOURCE_TEST})

target_link_libraries(test gtest_main stack)
target_link_options(test PUBLIC "-fsanitize=address" "-fsanitize=undefined")
target_link_options(stack PUBLIC "-fsanitize=address" "-fsanitize=undefined")

#clang-tidy
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    set(DO_CLANG_TIDY
        "${CLANG_TIDY}"
        clang-tidy: --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy
        -dump-config
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")

    #add_custom_target(tidy ALL)
    #add_custom_command(
    #    TARGET tidy
    #    COMMAND clang-tidy
    #    
    #    ${PROJECT_SOURCE_DIR}/${SOURCE_TEST}
    #    #${PROJECT_SOURCE_DIR}/${SOURCE_LIB}
    #    #${PROJECT_SOURCE_DIR}/${INC_DIR}/stack.hpp
    #    
    #    -dump-config
    #    --
    #    -I${PROJECT_SOURCE_DIR}/include
    #)
endif()

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(format ALL)
    add_custom_command(
        TARGET format
        COMMAND clang-format
        -i
        -style=file
        ${PROJECT_SOURCE_DIR}/${SOURCE_TEST}
        ${PROJECT_SOURCE_DIR}/${SOURCE_LIB}
        ${PROJECT_SOURCE_DIR}/${INC_DIR}/stack.hpp
    )
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SOURCE_TEST}
    ${SOURCE_LIB}
)



