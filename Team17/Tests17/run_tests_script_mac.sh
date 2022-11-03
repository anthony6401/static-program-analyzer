#!/bin/sh

cmake --build ../Code17/cmake-build-debug --target all &> /dev/null

echo "------ Running Unit Tests ------"
../Code17/cmake-build-debug/src/unit_testing/unit_testing

echo "------ Running Integration Tests ------"
../Code17/cmake-build-debug/src/integration_testing/integration_testing

echo "------ Running Autotester ------"
python3 regression_tester.py ../Code17/cmake-build-debug/src/autotester/autotester

rm -f default.profraw out.xml &> /dev/null