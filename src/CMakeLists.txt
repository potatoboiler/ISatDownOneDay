set(libsrc_list 
	DIMACS.hpp
	DIMACS.cpp
)

add_executable(SitDown 
	main.cpp 
	${libsrc_list}
)

target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_library(test_lib STATIC ${libsrc_list})
