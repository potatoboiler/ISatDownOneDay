cmake_minimum_required(VERSION 3.18)

# (name VERSION ver_number)
project(SitDown 
	VERSION 0.0
	DESCRIPTION "Satisfiability solver for learning purposes"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TEST "Build benchmarks and unit tests" ON)

add_subdirectory(src)

target_include_directories(SitDown PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
if (BUILD_TEST) 
	find_package(benchmark QUIET)

	# Also need to add a check that if BENCHMARK is not found in path,
	# git submodule add
	if (NOT benchmark_FOUND) 
		add_subdirectory(${CMAKE_SOURCE_DIR}/lib/benchmark)
	endif ()

	# target_link_libraries(SitDown PRIVATE benchmark::benchmark)

	find_package(Catch2 QUIET)

	add_subdirectory(test)
endif ()
