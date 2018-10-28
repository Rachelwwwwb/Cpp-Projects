# CMake generated Testfile for 
# Source directory: /home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests
# Build directory: /home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(*/MinHeapNumParam.add/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.add/*")
add_test(*/MinHeapNumParam.peek/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.peek/*")
add_test(*/MinHeapNumParam.rm/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.rm/*")
add_test(*/MinHeapNumParam.empty/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.empty/*")
add_test(*/MinHeapNumParam.peekTwoItems/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.peekTwoItems/*")
add_test(*/MinHeapNumParam.peekFiveItems/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.peekFiveItems/*")
add_test(*/MinHeapNumParam.PeekHundredItems/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.PeekHundredItems/*")
add_test(*/MinHeapNumParam.FillToTheBrimEmpty/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapNumParam.FillToTheBrimEmpty/*")
add_test(MinHeapNum.EmptyRemove "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapNum.EmptyRemove")
add_test(MinHeapNum.EmptyPeek "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapNum.EmptyPeek")
add_test(MinHeapString.add "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapString.add")
add_test(MinHeapString.peek "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapString.peek")
add_test(MinHeapString.rm "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapString.rm")
add_test(MinHeapString.empty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=MinHeapString.empty")
add_test(*/MinHeapSort.HeapSort100/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapSort.HeapSort100/*")
add_test(*/MinHeapSort.HeapSort543/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapSort.HeapSort543/*")
add_test(*/MinHeapSort.HeapSort1000/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw6/hw6-check/heap_tests/heap_test" "--gtest_filter=*/MinHeapSort.HeapSort1000/*")
