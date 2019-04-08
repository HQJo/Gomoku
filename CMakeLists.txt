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

#set(SOURCE_FILE src/AlphaBetaAI.h src/AlphaBetaAI.cpp src/gomoku.h test/test_evaluate.cpp src/gomoku.cpp test/test_search.cpp)
#add_executable(TEST_EVAL ${SOURCE_FILE})
#target_link_libraries(TEST_EVAL gtest gtest_main)

add_executable(MAIN src/gomoku.h src/horist.h  src/main.cpp src/gomoku.cpp src/horist.cpp src/GomokuAI.cpp src/GomokuAI.h)
