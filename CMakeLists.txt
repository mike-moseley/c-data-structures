cmake_minimum_required(VERSION 3.10)
project(c-data-structures)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE lib_sources
		"${CMAKE_SOURCE_DIR}/src/*.c"
)
add_library(cds STATIC ${lib_sources})
target_include_directories(cds PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_compile_options(cds PRIVATE -Wall -Wextra -g -pedantic)

# Unity testing
enable_testing()

set(UNITY_SRC "${CMAKE_SOURCE_DIR}/test/unity/unity.c")

# Each test needs to be appended below
add_custom_target(tests DEPENDS test_example test_linked_list test_doubly_linked_list test_slice test_hash_map)

# Begin test block; copy this block for each test file
add_executable(test_example
	test/test_example.c
	${UNITY_SRC}
)
target_link_libraries(test_example PRIVATE cds)
set_target_properties(test_example PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_example PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
)
target_compile_options(test_example PRIVATE -Wall -Wextra -g)

add_executable(test_linked_list
	test/test_linked_list.c
	${UNITY_SRC}
)
target_link_libraries(test_linked_list PRIVATE cds)
set_target_properties(test_linked_list PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_linked_list PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
)
target_compile_options(test_linked_list PRIVATE -Wall -Wextra -g)

add_executable(test_doubly_linked_list
	test/test_doubly_linked_list.c
	${UNITY_SRC}
)
target_link_libraries(test_doubly_linked_list PRIVATE cds)
set_target_properties(test_doubly_linked_list PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_doubly_linked_list PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
)
target_compile_options(test_doubly_linked_list PRIVATE -Wall -Wextra -g)

add_executable(test_slice
	test/test_slice.c
	${UNITY_SRC}
)
target_link_libraries(test_slice PRIVATE cds)
set_target_properties(test_slice PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_slice PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
)
target_compile_options(test_slice PRIVATE -Wall -Wextra -g)

add_executable(test_hash_map
	test/test_hash_map.c
	${UNITY_SRC}
)
target_link_libraries(test_hash_map PRIVATE cds)
set_target_properties(test_hash_map PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_hash_map PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
)
target_compile_options(test_hash_map PRIVATE -Wall -Wextra -g)

add_test(NAME example COMMAND test_example)
add_test(NAME linked_list COMMAND test_linked_list)
add_test(NAME doubly_linked_list COMMAND test_doubly_linked_list)
add_test(NAME slice COMMAND test_slice)
add_test(NAME hash_map COMMAND test_hash_map)
# End test block.
