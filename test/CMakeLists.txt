if (NOT Catch2_FOUND)
	set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
	# add_library(Catch2 STATIC ${CATCH_INCLUDE_DIR}/catch.hpp)
	add_library(Catch2 STATIC ${CATCH_INCLUDE_DIR}/catch_amalgamated.hpp)
	set_target_properties(Catch2 PROPERTIES LINKER_LANGUAGE CXX)
endif()

add_executable(catch_test 
	catch_test.cpp
	dimacs_tests.cpp
	${CMAKE_SOURCE_DIR}/src/DIMACS.cpp
	${CMAKE_SOURCE_DIR}/src/SitDown-v1.cpp
	${CMAKE_SOURCE_DIR}/src/clause.cpp
)

if (NOT Catch2_FOUND)
	target_link_libraries(catch_test PRIVATE Catch2)
	target_include_directories(catch_test PRIVATE ${CATCH_INCLUDE_DIR})
endif ()

# Add library of functions for linking to testing executable
target_link_libraries(catch_test PRIVATE test_lib)

# add_test(NAME dimacs_test COMMAND catch_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test/test_dimacs)
file(COPY test_dimacs DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})