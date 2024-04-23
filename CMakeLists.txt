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
	dynamic_programming/coin_change.cpp
	dynamic_programming/max_increasing_subarray.cpp
	dynamic_programming/grid_path.cpp
	dynamic_programming/knapsack_packing.cpp

	sorting/bubble_sort.cpp
	sorting/sweeping_line_algorithm.cpp
	sorting/selection_sort.cpp
	sorting/merge_sort.cpp
	sorting/quick_sort.cpp

	greedy_algorithms/work_schedule.cpp
	greedy_algorithms/time_table.cpp

	search/binary_search.cpp

	numeric/power.cpp
	numeric/greatest_common_divisor.cpp
	numeric/itoa.cpp
	numeric/fast_fourier_transform.cpp

	graphs/depth_first_search.cpp
	graphs/breadth_first_search.cpp
	graphs/cycle_detection.cpp

	graphs/shortest_path/bellman_ford.cpp
	graphs/shortest_path/dijkstra.cpp
	graphs/shortest_path/floyd_warshall.cpp

	two_pointers/given_sum_subarray.cpp
	two_pointers/remove_element.cpp

	tree/diameter.cpp
)

if(MSVC)
  add_compile_options(algorithm_curriculum /W4 /WX)
  set_property(TARGET algorithm_curriculum PROPERTY
	MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL<$<CONFIG:Debug>:Debug>")
  set_property(TARGET algorithm_curriculum PROPERTY
	MSVC_RUNTIME_LIBRARY "MultiThreadedDLL<$<CONFIG:Release>:Release>")
else()
  add_compile_options(algorithm_curriculum -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(algorithm_curriculum
  GTest::gtest_main
)
