cmake_minimum_required(VERSION 3.13)
project(Gomoku)
set(CMAKE_CXX_STANDARD 17)


set(GTEST_SRC_DIR ./lib/googletest)
add_subdirectory(${GTEST_SRC_DIR})
include_directories(${GTEST_SRC_DIR}/include)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

set(SOURCE_FILE src/gomoku.h src/gomoku.cpp src/horist.h src/horist.cpp
        src/GameBoard.h src/GameBoard.cpp src/GomokuAI.h src/GomokuAI.cpp)
add_executable(TEST_EVAL ${SOURCE_FILE} test/test_evaluate.cpp)
add_executable(TEST_SEARCH ${SOURCE_FILE} test/test_search.cpp)
target_link_libraries(TEST_EVAL gtest gtest_main)
target_link_libraries(TEST_SEARCH gtest gtest_main)

add_executable(MAIN ${SOURCE_FILE})
