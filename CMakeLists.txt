cmake_minimum_required(VERSION 3.10)
project(DataStructures C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Main executable source file
set(MAIN_SOURCE_FILE test.c)

# Gather all other .c files from subdirectories (excluding c_refresh and DynamicArray)
file(GLOB_RECURSE DATA_STRUCTURE_SOURCES
    "avl_tree/*.c"
    "binary_heap/*.c"
    "binary_search_tree/*.c"
    "deque/*.c"
    "disjoint_set_union/*.c"
    "doubly_linked_list/*.c"
    "fenwick_tree/*.c"
    "graph_adj_list/*.c"
    "graph_adj_matrix/*.c"
    "hash_set/*.c"
    "queue/*.c"
    "red_black_tree/*.c"
    "rope/*.c"
    "segment_tree/*.c"
    "singly_linked_list/*.c"
    "skip_list/*.c"
    "stack/*.c"
    "trie/*.c"
    "vector/*.c"
)

# Add all sources for the executable
add_executable(test_program ${MAIN_SOURCE_FILE} ${DATA_STRUCTURE_SOURCES})

# Add include directories
target_include_directories(test_program PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/avl_tree"
    "${CMAKE_CURRENT_SOURCE_DIR}/binary_heap"
    "${CMAKE_CURRENT_SOURCE_DIR}/binary_search_tree"
    "${CMAKE_CURRENT_SOURCE_DIR}/deque"
    "${CMAKE_CURRENT_SOURCE_DIR}/disjoint_set_union"
    "${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list"
    "${CMAKE_CURRENT_SOURCE_DIR}/fenwick_tree"
    "${CMAKE_CURRENT_SOURCE_DIR}/graph_adj_list"
    "${CMAKE_CURRENT_SOURCE_DIR}/graph_adj_matrix"
    "${CMAKE_CURRENT_SOURCE_DIR}/hash_set"
    "${CMAKE_CURRENT_SOURCE_DIR}/queue"
    "${CMAKE_CURRENT_SOURCE_DIR}/red_black_tree"
    "${CMAKE_CURRENT_SOURCE_DIR}/rope"
    "${CMAKE_CURRENT_SOURCE_DIR}/segment_tree"
    "${CMAKE_CURRENT_SOURCE_DIR}/singly_linked_list"
    "${CMAKE_CURRENT_SOURCE_DIR}/skip_list"
    "${CMAKE_CURRENT_SOURCE_DIR}/stack"
    "${CMAKE_CURRENT_SOURCE_DIR}/trie"
    "${CMAKE_CURRENT_SOURCE_DIR}/vector"
)

# Optional: Add compiler flags (e.g., for warnings and debug symbols)
target_compile_options(test_program PRIVATE -Wall -g)

# Print a message when configuration is done
message(STATUS "CMake configuration complete. To build, run 'make' in your build directory.")
