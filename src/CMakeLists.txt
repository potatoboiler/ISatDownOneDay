add_executable(SitDown main.cpp DIMACS.hpp DIMACS.cpp)

target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(test_lib STATIC
	DIMACS.hpp
	DIMACS.cpp
)
