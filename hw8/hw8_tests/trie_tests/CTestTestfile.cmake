# CMake generated Testfile for 
# Source directory: /home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests
# Build directory: /home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Trie.ConstructionDestruction "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=Trie.ConstructionDestruction")
add_test(Trie.FindEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=Trie.FindEmpty")
add_test(TrieInsert.OneLetterFind "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.OneLetterFind")
add_test(TrieInsert.OtherLetterFind "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.OtherLetterFind")
add_test(TrieInsert.OneWordFind "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.OneWordFind")
add_test(TrieInsert.Substring "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.Substring")
add_test(TrieInsert.SubstringInsert "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.SubstringInsert")
add_test(TrieInsert.SplitTree "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsert.SplitTree")
add_test(TrieRemove.Empty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.Empty")
add_test(TrieRemove.Nonexistant "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.Nonexistant")
add_test(TrieRemove.OneLetter "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.OneLetter")
add_test(TrieRemove.OneWord "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.OneWord")
add_test(TrieRemove.UselessNodesRemoved "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.UselessNodesRemoved")
add_test(TrieRemove.NotInSet "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.NotInSet")
add_test(TrieRemove.Superstring "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.Superstring")
add_test(TrieRemove.Substring "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.Substring")
add_test(TrieRemove.SplitTreeRemoveLeaf "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.SplitTreeRemoveLeaf")
add_test(TrieRemove.SplitTreeRemoveRoot "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemove.SplitTreeRemoveRoot")
add_test(TrieInsertStress.Random50x30ele "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsertStress.Random50x30ele")
add_test(TrieInsertStress.Random3x1000ele "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsertStress.Random3x1000ele")
add_test(TrieInsertStress.Random3xUltralongWords "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsertStress.Random3xUltralongWords")
add_test(TrieInsertStress.NotInSet "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieInsertStress.NotInSet")
add_test(TrieRemoveStress.RandomBuildupBreakdown "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw8/hw8_tests/trie_tests/trie_tests" "--gtest_filter=TrieRemoveStress.RandomBuildupBreakdown")
