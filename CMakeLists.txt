cmake_minimum_required(VERSION 3.13)
project(Gomoku)
set(CMAKE_CXX_STANDARD 14)


set(GTEST_SRC_DIR ./lib/googletest)
add_subdirectory(${GTEST_SRC_DIR})
include_directories(${GTEST_SRC_DIR}/include)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

#add_executable(Gomoku main.cpp search.h gomoku.h)
set(SOURCE_FILE src/search.h src/gomoku.h test/test.cpp)
add_executable(TEST_EVAL ${SOURCE_FILE})
target_link_libraries(TEST_EVAL gtest gtest_main)

add_executable(MAIN src/search.h src/gomoku.h src/main.cpp)
