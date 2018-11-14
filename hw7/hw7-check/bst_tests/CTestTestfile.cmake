# CMake generated Testfile for 
# Source directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests
# Build directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BSTTestIntStr.CreateDestroy "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.CreateDestroy")
add_test(BSTTestIntStr.AddSingleItem "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.AddSingleItem")
add_test(BSTTestIntStr.SingleItemBalanced "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.SingleItemBalanced")
add_test(BSTTestIntStr.SingleItemRemove "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.SingleItemRemove")
add_test(BSTTestIntStr.SingleItemClear "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.SingleItemClear")
add_test(BSTTestIntStr.AddFiveItems "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestIntStr.AddFiveItems")
add_test(BSTTestInt.DuplicateKeys "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.DuplicateKeys")
add_test(BSTTestInt.AddFiveItemsIterate "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.AddFiveItemsIterate")
add_test(BSTTestInt.AddFiveRemoveRoot "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.AddFiveRemoveRoot")
add_test(BSTTestInt.AddRemoveFive "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.AddRemoveFive")
add_test(BSTTestInt.DirectPredecessor "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.DirectPredecessor")
add_test(BSTTestInt.IndirectPredecessorLeftChild "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=BSTTestInt.IndirectPredecessorLeftChild")
add_test(*/BSTSort.StressSort/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=*/BSTSort.StressSort/*")
add_test(*/BSTSort.StressSortRemove/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/bst_tests/bst_test" "--gtest_filter=*/BSTSort.StressSortRemove/*")
