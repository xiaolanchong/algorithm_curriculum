cmake_minimum_required(VERSION 3.13)
project(algorithm_curriculum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

include_directories(googletest/googletest/include)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(algorithm_curriculum
	recursion/all_permutations.cpp
	recursion/queen_puzzle.cpp

	dynamic_programming/max_sum_subarray.cpp
)

if(MSVC)
  add_compile_options(algorithm_curriculum /W4 /WX)
else()
  add_compile_options(algorithm_curriculum -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(algorithm_curriculum
  GTest::gtest_main
)
