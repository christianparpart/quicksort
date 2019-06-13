cmake_minimum_required(VERSION 3.0)
project(quicksort)

find_program(
	CLANG_TIDY_EXE
	NAMES "clang-tidy"
	DOC "Path to clang-tidy executable"
)
if(NOT CLANG_TIDY_EXE)
	message(STATUS "clang-tidy not found.")
else()
	message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
	set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

add_executable(test_sort test_sort.cpp)
set_target_properties(test_sort PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
