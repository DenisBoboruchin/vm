set(HASH_TABLE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_PARRENT_PATH)
include_directories (${PROJECT_PARRENT_PATH}/queue/list/include)

set (PROJECT_NAME hash_table)

add_subdirectory (tests)
