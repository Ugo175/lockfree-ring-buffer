cmake_minimum_required(VERSION 3.16)
project(lockfree_ring_buffer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall  -Wextra  -O2)

option(ENABLE_TSAN "Build with ThreadSanitizer" OFF)
if (ENABLE_TSAN)
	add_compile_options(-fsanitize=thread -g)
	add_link_options(-fsanitizer=thread)
endif()

add_library(ring_buffer INTERFACE)
target_include_directories(ring_buffer INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(packet_processor src/main.cpp)
target_link_libraries(packet_processor PRIVATE ring_buffer)

add_executable(test_ring_buffer tests/test_ring_buffer.cpp)
target_link_libraries(test_ring_buffer PRIVATE ring_buffer)

add_executable(bench_ring_buffer benchmarks/bench_ring_buffer.cpp)
target_link_libraries(bench_ring_buffer PRIVATE ring_buffer)
