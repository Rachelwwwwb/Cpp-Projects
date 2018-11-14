# CMake generated Testfile for 
# Source directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests
# Build directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AVLTestInt.CreateDestroy "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.CreateDestroy")
add_test(AVLTestInt.AddSingle "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.AddSingle")
add_test(AVLTestInt.AddTwo "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.AddTwo")
add_test(AVLTestInt.AddDuplicateKeys "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.AddDuplicateKeys")
add_test(AVLTestInt.ZigZigOne "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.ZigZigOne")
add_test(AVLTestInt.ZigZigLarge "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.ZigZigLarge")
add_test(AVLTestInt.ZigZagOne "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.ZigZagOne")
add_test(AVLTestInt.ZigZigRemoveUnbalanced "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.ZigZigRemoveUnbalanced")
add_test(AVLTestInt.ZigZigRemoveTwoUnbalanced "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.ZigZigRemoveTwoUnbalanced")
add_test(AVLTestInt.SingleChildRemoveBalanced "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.SingleChildRemoveBalanced")
add_test(AVLTestInt.TwoChildRemoveUnbalanced "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/avl_tests/avl_test" "--gtest_filter=AVLTestInt.TwoChildRemoveUnbalanced")
