set(libutil_list 
	DIMACS.hpp
	DIMACS.cpp
)

set(libsrc_list
	SitDown-v1.hpp
	SitDown-v1.cpp
	types.hpp
	clause.hpp
)

add_executable(SitDown 
	main.cpp 
	${libsrc_list}
	${libutil_list}
)

target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(test_lib STATIC ${libsrc_list})
