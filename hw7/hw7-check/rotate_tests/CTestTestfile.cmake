# CMake generated Testfile for 
# Source directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests
# Build directory: /home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(RotateInt.Create "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests/rotate_test" "--gtest_filter=RotateInt.Create")
add_test(*/RotateIntTransform.LimitedTransform/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests/rotate_test" "--gtest_filter=*/RotateIntTransform.LimitedTransform/*")
add_test(*/RotateMass.MassSameKeys/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests/rotate_test" "--gtest_filter=*/RotateMass.MassSameKeys/*")
add_test(*/RotateMass.MassTransform/* "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104~/hw-wenbeiwa/hw7/hw7-check/rotate_tests/rotate_test" "--gtest_filter=*/RotateMass.MassTransform/*")
