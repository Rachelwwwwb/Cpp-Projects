//
// Created by cs104 on 12/10/18.
//

#include "trie_checker.h"

#include <misc_utils.h>

#include <iostream>

#define TRIE_NODE_CHILDREN ('z'-'a' + 1)

/**
 * Recursively walks the given subtrie and adds any words it found to foundWords
 * @param correctParent pointer to the actual parent node of this subtrie root. nullptr if there is no parent.
 * @param nodeString string of characters leading from the base of the trie to the current subtree root node
 */
testing::AssertionResult walkTrie(TrieNode * subtrieRoot, TrieNode * correctParent, std::string const & nodeString, std::set<std::string> & foundWords)
{
	if(subtrieRoot == nullptr)
	{
		// base case: empty subtree
		return testing::AssertionSuccess();
	}

	// check parent pointer
	if(correctParent != nullptr && correctParent != subtrieRoot->parent)
	{
		std::cout << "Warning: Incorrect parent pointer on node " << nodeString << " (mismatch with actual parent in tree)" << std::endl;
	}

	// check if the current node is useless (no children and not in set)
	if(!subtrieRoot->inSet)
	{
		bool hasChildren = false;
		for(size_t childIndex = 0; childIndex < TRIE_NODE_CHILDREN; ++childIndex)
		{
			if(subtrieRoot->children[childIndex] != nullptr)
			{
				hasChildren = true;
				break;
			}
		}

		if(!hasChildren)
		{
			return testing::AssertionFailure() << "Node " << nodeString << " is useless (no children and not in set), and should have been removed!";
		}
	}

	// if it's in the set, add this to the set of discovered words
	if(subtrieRoot->inSet)
	{
		foundWords.insert(nodeString);
	}

	// now, recurse to all children
	for(size_t childIndex = 0; childIndex < TRIE_NODE_CHILDREN; ++childIndex)
	{
		char currentChar = static_cast<char>('a' + childIndex);

		testing::AssertionResult childResult =  walkTrie(subtrieRoot->children[childIndex], subtrieRoot, nodeString + currentChar, foundWords);

		if(!childResult)
		{
			return childResult;
		}
	}

	return testing::AssertionSuccess();
}


testing::AssertionResult verifyTrie(TrieSet & trie, std::set<std::string> const & expectedWords)
{
	// first issue: we need to get the root node, and that's supposed to be returned by calling prefix with an empty string
	// however, this was only communicated through a Piazza post, and many students seem to have missed it.
	// So, we get a node one below the root and look at the parent pointer

	if(expectedWords.empty())
	{
		// nothing to check anyway...
		return testing::AssertionSuccess();
	}

	std::string checkingString = *expectedWords.begin();
	char checkingChar = checkingString[0];
	TrieNode * topLevelNode = trie.prefix(std::string(1, checkingChar));

	if(topLevelNode == nullptr)
	{
		return testing::AssertionFailure() << "trie was supposed to contain node " << checkingString << ", but did not contain a top-level node for character " << checkingChar;
	}

	if(topLevelNode->parent == nullptr)
	{
		return testing::AssertionFailure() << "node found for string " << checkingChar << " was supposed to be at the top level, but its parent was null instead of the root node";
	}

	TrieNode * rootNode = topLevelNode->parent;

	// now, walk through trie to check structure
	std::set<std::string> foundWords;
	testing::AssertionResult walkResult = walkTrie(rootNode, nullptr, "", foundWords);

	if(!walkResult)
	{
		// trie structure error
		return walkResult;
	}

	if(foundWords != expectedWords)
	{
		return testing::AssertionFailure() << "Contents do not match expected contents!  Expected contents: " << setToString(expectedWords) << ", actual contents: " << setToString(foundWords);
	}

	return testing::AssertionSuccess();

}
