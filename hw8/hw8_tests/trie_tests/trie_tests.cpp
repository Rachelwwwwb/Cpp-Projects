#include "trie_checker.h"

#include <random_generator.h>

#include <gtest/gtest.h>

TEST(Trie, ConstructionDestruction)
{
	TrieSet trie;
}

TEST(Trie, FindEmpty)
{
	TrieSet trie;

	ASSERT_EQ(nullptr, trie.prefix("s"));
}

TEST(TrieInsert, OneLetterFind)
{
	TrieSet trie;

	trie.insert("r");

	ASSERT_NE(nullptr, trie.prefix("r"));
}

TEST(TrieInsert, OtherLetterFind)
{
	TrieSet trie;

	trie.insert("r");

	ASSERT_EQ(nullptr, trie.prefix("s"));
}

TEST(TrieInsert, OneWordFind)
{
	TrieSet trie;

	trie.insert("all");

	EXPECT_IN_SET(trie, "all")
}

TEST(TrieInsert, Substring)
{
	TrieSet trie;

	trie.insert("allies");

	EXPECT_NOT_IN_SET(trie, "all")
	EXPECT_IN_SET(trie, "allies");
}

TEST(TrieInsert, SubstringInsert)
{
	TrieSet trie;

	trie.insert("allies");

	EXPECT_NOT_IN_SET(trie, "all")
	EXPECT_IN_SET(trie, "allies");

	trie.insert("all");

	// now "all" should be in the trie
	EXPECT_IN_SET(trie, "all");
}

TEST(TrieInsert, SplitTree)
{
	TrieSet trie;

	trie.insert("allies");
	trie.insert("alliance");

	EXPECT_NOT_IN_SET(trie, "alli")
	EXPECT_IN_SET(trie, "allies");
	EXPECT_IN_SET(trie, "alliance");
}

TEST(TrieRemove, Empty)
{
	TrieSet trie;

	trie.remove("supercalifragilisticexpialodocious");

	ASSERT_EQ(nullptr, trie.prefix("supercalifragilisticexpialodocious"));
}

TEST(TrieRemove, Nonexistant)
{
	TrieSet trie;

	trie.insert("foo");

	trie.remove("supercalifragilisticexpialodocious");

	ASSERT_EQ(nullptr, trie.prefix("supercalifragilisticexpialodocious"));
}

TEST(TrieRemove, OneLetter)
{
	TrieSet trie;

	trie.insert("r");

	ASSERT_NE(nullptr, trie.prefix("r"));

	trie.remove("r");

	ASSERT_EQ(nullptr, trie.prefix("r"));
}

TEST(TrieRemove, OneWord)
{
	TrieSet trie;

	trie.insert("fred");

	ASSERT_NE(nullptr, trie.prefix("fred"));

	trie.remove("fred");

	ASSERT_EQ(nullptr, trie.prefix("fred"));
}


TEST(TrieRemove, UselessNodesRemoved)
{
	TrieSet trie;

	trie.insert("isotropic");

	EXPECT_NOT_IN_SET(trie, "iso");
	EXPECT_IN_SET(trie, "isotropic");

	trie.remove("isotropic");

	EXPECT_EQ(nullptr, trie.prefix("isotropic"));
	EXPECT_EQ(nullptr, trie.prefix("iso"));
}

TEST(TrieRemove, NotInSet)
{
	TrieSet trie;

	trie.insert("isotropic");

	EXPECT_NOT_IN_SET(trie, "iso");
	EXPECT_IN_SET(trie, "isotropic");

	trie.remove("iso");

	// nothing should be changed
	EXPECT_NOT_IN_SET(trie, "iso");
	EXPECT_IN_SET(trie, "isotropic");
}


TEST(TrieRemove, Superstring)
{
	TrieSet trie;

	trie.insert("isotropic");
	trie.insert("iso");

	EXPECT_IN_SET(trie, "iso")
	EXPECT_IN_SET(trie, "isotropic");

	trie.remove("isotropic");

	EXPECT_EQ(nullptr, trie.prefix("isotropic"));
	EXPECT_IN_SET(trie, "iso");
}

TEST(TrieRemove, Substring)
{
	TrieSet trie;

	trie.insert("isotropic");
	trie.insert("iso");

	EXPECT_IN_SET(trie, "iso")
	EXPECT_IN_SET(trie, "isotropic");

	trie.remove("iso");

	EXPECT_IN_SET(trie, "isotropic");
	EXPECT_NOT_IN_SET(trie, "iso")
}

TEST(TrieRemove, SplitTreeRemoveLeaf)
{
	TrieSet trie;

	trie.insert("isomorphic");
	trie.insert("isotropic");

	EXPECT_NOT_IN_SET(trie, "iso")
	EXPECT_IN_SET(trie, "isotropic");
	EXPECT_IN_SET(trie, "isomorphic");

	trie.remove("isomorphic");

	EXPECT_IN_SET(trie, "isotropic");
	EXPECT_NOT_IN_SET(trie, "iso")
	EXPECT_EQ(nullptr, trie.prefix("isomorphic"));
}

TEST(TrieRemove, SplitTreeRemoveRoot)
{
	TrieSet trie;

	trie.insert("isomorphic");
	trie.insert("isotropic");
	trie.insert("iso");
	trie.insert("isosceles");

	EXPECT_IN_SET(trie, "iso")
	EXPECT_IN_SET(trie, "isotropic");
	EXPECT_IN_SET(trie, "isomorphic");
	EXPECT_IN_SET(trie, "isosceles");

	trie.remove("iso");

	EXPECT_NOT_IN_SET(trie, "iso")
	EXPECT_IN_SET(trie, "isotropic");
	EXPECT_IN_SET(trie, "isomorphic");
	EXPECT_IN_SET(trie, "isosceles");
}

TEST(TrieInsertStress, Random50x30ele)
{
	const size_t numElements = 30;
	const size_t numTrials = 50;
	const size_t wordLength = 8;
	const RandomSeed masterSeed = 9387;

	std::vector<RandomSeed> trialSeeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed seed : trialSeeds)
	{
		TrieSet trie;

		std::set<std::string> words = makeRandomAlphaStringSet(numElements, seed, wordLength);

		for(std::string const & word : words)
		{
			trie.insert(word);
		}

		EXPECT_TRUE(verifyTrie(trie, words));
	}
}

TEST(TrieInsertStress, Random3x1000ele)
{
	const size_t numElements = 1000;
	const size_t numTrials = 3;
	const size_t wordLength = 8;
	const RandomSeed masterSeed = 786;

	std::vector<RandomSeed> trialSeeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed seed : trialSeeds)
	{
		TrieSet trie;

		std::vector<std::string> words = makeRandomAlphaStringVector(numElements, seed, wordLength, false);
		std::set<std::string> wordsSet = std::set<std::string>(words.begin(), words.end());

		for(std::string const & word : words)
		{
			trie.insert(word);
		}

		EXPECT_TRUE(verifyTrie(trie, wordsSet));
	}
}

TEST(TrieInsertStress, Random3xUltralongWords)
{
	const size_t numElements = 3;
	const size_t numTrials = 3;
	const size_t wordLength = 2000;
	const RandomSeed masterSeed = 6791;

	std::vector<RandomSeed> trialSeeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed seed : trialSeeds)
	{
		TrieSet trie;

		std::vector<std::string> words = makeRandomAlphaStringVector(numElements, seed, wordLength, false);
		std::set<std::string> wordsSet = std::set<std::string>(words.begin(), words.end());

		for(std::string const & word : words)
		{
			trie.insert(word);
		}

		EXPECT_TRUE(verifyTrie(trie, wordsSet));
	}
}

TEST(TrieInsertStress, NotInSet)
{
	const size_t numElements = 30;
	const size_t numTrials = 50;
	const size_t wordLength = 8;
	const RandomSeed masterSeed = 7;

	std::vector<RandomSeed> trialSeeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed seed : trialSeeds)
	{
		TrieSet trie;

		std::set<std::string> inSetWords = makeRandomAlphaStringSet(numElements, seed, wordLength);
		std::set<std::string> notInSetWords = makeRandomAlphaStringSet(numElements, seed + 8, wordLength);

		for(std::string const & word : inSetWords)
		{
			trie.insert(word);
		}

		// check that all not-in-set words are not in fact in the set
		for(std::string const & word : notInSetWords)
		{
			// it's unlikely, but there could still be duplicates
			if(inSetWords.find(word) == inSetWords.end())
			{
				EXPECT_TRUE(trie.prefix(word) == nullptr || (!trie.prefix(word)->inSet));
			}
		}
	}
}

TEST(TrieRemoveStress, RandomBuildupBreakdown)
{
	const size_t numElements = 30;
	const size_t numTrials = 25;
	const size_t wordLength = 8;
	const RandomSeed masterSeed = 43;

	std::vector<RandomSeed> trialSeeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed seed : trialSeeds)
	{
		TrieSet trie;

		std::vector<std::string> words = makeRandomAlphaStringVector(numElements, seed, wordLength, false);

		for(std::string const & word : words)
		{
			trie.insert(word);
		}

		std::set<std::string> currentContents(words.begin(), words.end());

		for(std::string const & word : words)
		{
			// note: verifyTrie() doesn't handle empty tries, so we do it before each remove so in the last iteration it'll still have 1 element
			EXPECT_TRUE(verifyTrie(trie, currentContents));

			trie.remove(word);
			currentContents.erase(word);
		}


	}
}

