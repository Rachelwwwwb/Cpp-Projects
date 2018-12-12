
set(TRIE_TESTS_SOURCES
    trie_checker.cpp
    trie_tests.cpp)

add_executable(trie_tests ${TRIE_TESTS_SOURCES})
target_link_libraries(trie_tests gtest gtest_main testing_utils hw8_trie)

add_valgrind_gtests(trie_tests)