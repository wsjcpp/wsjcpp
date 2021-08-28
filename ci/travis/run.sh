#!/bin/bash

check_ret() {
    if [ $1 -ne 0 ]; then
        echo ""
        echo "!!! FAIL: $2"
        echo "********************************************************************************"
        echo ""
        exit $1
    else
        echo ""
        echo "*** SUCCESS: $2"
        echo "********************************************************************************"
        echo ""
    fi
}

./build_simple.sh
check_ret $? "build"
cd ./tests/
check_ret $? "cd tests"
./run_package_installation.sh
check_ret $? "run_package_installation"
cd ../unit-tests.wsjcpp
check_ret $? "cd tests"
./build_simple.sh
check_ret $? "build tests"
./unit-tests
check_ret $? "unit-tests"