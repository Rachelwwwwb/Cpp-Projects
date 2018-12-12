cmake_minimum_required(VERSION 3.4)

message("########################################################")
message("                 CS104 HW8 Test Suite")
message("########################################################")

project(CS104-HW8-Test-Suite C CXX)

# pick up include files
# ----------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/test_cmake_lib)

include(Policies NO_POLICY_SCOPE)
include(Utils)
include(Shorthand)
include(LibraryUtils)
include(104CompileFlags)

# setup Valgrind
# ----------------------------------------------------------

find_program(VALGRIND NAMES valgrind DOC "Path to valgrind executable")
import_executable(valgrind ${VALGRIND})

set(VALGRIND_ARGS --tool=memcheck 
	--leak-check=yes
	--trace-children=no) # don't valgrind child processes, we control manually which processes are valground

# find GTest
# ----------------------------------------------------------

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

import_libraries(gtest LIBRARIES ${GTEST_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})
import_libraries(gtest_main LIBRARIES ${GTEST_MAIN_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})

include(CustomTests)
enable_testing()

# find user code dir
# ----------------------------------------------------------

if(NOT DEFINED HW8_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.h")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw8 dir, or run CMake with the \"-DHW8_DIR=<path to hw8>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW8_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW8_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw8 assignment directory")
	endif()
endif()

# make sure HW8_DIR is an absolute path
get_filename_component(HW8_DIR "${HW8_DIR}" REALPATH)

# build loose user code as a CMake library
# ----------------------------------------------------------

# note: lots of students ended up putting Trie.h in a subfolder, so search for it and its headers recursively
file(GLOB_RECURSE TRIE_CPP_FILE LIST_DIRECTORIES FALSE "${HW8_DIR}/*Trie.cpp")

if(NOT TRIE_CPP_FILE)
	message(WARNING "Cannot locate Trie.cpp in ${HW8_DIR}.  Attempting to continue configuration...")

	# make a dummy interface target so that it can at least get through the confiuration stage
	add_library(hw8_trie INTERFACE)
	target_include_directories(hw8_trie INTERFACE ${HW8_DIR})
else()

	message(STATUS "Trie.cpp found via recursive match: ${TRIE_CPP_FILE}")

	add_library(hw8_trie STATIC ${TRIE_CPP_FILE})

	# now, find every directory with header files in it and include those
	set(HEADER_FILE_DIRS )
	file(GLOB_RECURSE ALL_HEADER_FILES LIST_DIRECTORIES FALSE "${HW8_DIR}/*.h*")
	foreach(HEADER_FILE ${ALL_HEADER_FILES})

		get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)

		# if we haven't seen this one, add it to the list
		if(NOT "${HEADER_DIR}" IN_LIST HEADER_FILE_DIRS)
			message(STATUS "Header files found, including directory ${HEADER_DIR}")
			list(APPEND HEADER_FILE_DIRS ${HEADER_DIR})
		endif()

	endforeach()

	target_include_directories(hw8_trie PUBLIC ${HW8_DIR} ${HEADER_FILE_DIRS})
endif()

# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(trie_tests)

set(TEST_TIMEOUT 30) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling trie, output saved to ${COMPILE_LOG_DIR}/trie.complog" #
	COMMAND make hw8_trie 1>${COMPILE_LOG_DIR}/trie.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling unit tests"
	COMMAND make trie_tests || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})