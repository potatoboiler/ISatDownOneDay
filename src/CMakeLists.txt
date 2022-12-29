set(libsrc_list 
	DIMACS.hpp
	DIMACS.cpp
)

add_executable(SitDown 
	main.cpp 
	SitDown-v1.hpp
	SitDown-v1.cpp
	${libsrc_list}
)

target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(SitDown PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(test_lib STATIC ${libsrc_list})
