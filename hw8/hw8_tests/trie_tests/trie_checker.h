//
// CS104 Trie automatic checking functions
//

#ifndef CS104_HW8_TEST_SUITE_TRIE_CHECKER_H
#define CS104_HW8_TEST_SUITE_TRIE_CHECKER_H

#include <Trie.h>

#include <gtest/gtest.h>

#include <string>
#include <set>

/**
 * Verifies that a trie is structured correctly and has the expected words.
 *
 * NOTE: does nothing if expectedWords is empty, ane expectedWords shouldn't contain any empty strings.
 * @param trie
 * @param expectedWords
 * @return
 */
testing::AssertionResult verifyTrie(TrieSet & trie, std::set<std::string> const & expectedWords);

// some macros to make test writing easier
// these macros verify that a node exists, and is or is not in the set
#define EXPECT_IN_SET(trie, string) \
{ \
	TrieNode * result = trie.prefix(string); \
	/* make sure to check for null pointers first */ \
	ASSERT_NE(nullptr, result); \
	EXPECT_TRUE(result->inSet); \
}

#define EXPECT_NOT_IN_SET(trie, string) \
{ \
	TrieNode * result = trie.prefix(string); \
	ASSERT_NE(nullptr, result); \
	EXPECT_FALSE(result->inSet); \
}

#endif //CS104_HW8_TEST_SUITE_TRIE_CHECKER_H
