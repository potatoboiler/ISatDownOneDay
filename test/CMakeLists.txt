if (NOT Catch2_FOUND)
	set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
	add_library(Catch2 STATIC ${CATCH_INCLUDE_DIR}/catch.hpp)
	set_target_properties(Catch2 PROPERTIES LINKER_LANGUAGE CXX)
endif()

add_executable(catch_test 
	catch_test.cpp
	dimacs_tests.cpp
)

if (NOT Catch2_FOUND)
	target_link_libraries(catch_test PRIVATE Catch2)
	target_include_directories(catch_test PRIVATE ${CATCH_INCLUDE_DIR})
endif ()

# Add library of functions for linking to testing executable
target_link_libraries(catch_test PRIVATE test_lib)
