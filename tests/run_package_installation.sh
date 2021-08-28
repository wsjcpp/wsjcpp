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

# from http

cd ..
./wsjcpp install https://wsjcpp.org/packages/example-wsjcpp-package-https/v0.0.1/
check_ret $? "Problem with install https://wsjcpp.org/packages/example-wsjcpp-package-https/v0.0.1/"
EXPECTED_DIR="./src.wsjcpp/example_wsjcpp_package_https"
if [ ! -d $EXPECTED_DIR ]; then
    echo "Not found dir "$EXPECTED_DIR
    exit 1
fi
./build_simple.sh
check_ret $? "Could not rebuild project"

./wsjcpp uninstall https://wsjcpp.org/packages/example-wsjcpp-package-https/v0.0.1/
check_ret $? "problem with uninstall example-wsjcpp-package-https"
if [ -d $EXPECTED_DIR ]; then
    echo "Found directory "$EXPECTED_DIR
    exit 1
fi

# from localfs
./wsjcpp install ./tests/example-wsjcpp-package-localfs
check_ret $? "Problem with install ./src.wsjcpp/example_wsjcpp_package_localfs"
EXPECTED_DIR="./src.wsjcpp/example_wsjcpp_package_localfs"
if [ ! -d $EXPECTED_DIR ]; then
    echo "Not found dir "$EXPECTED_DIR
    exit 1
fi
./build_simple.sh
check_ret $? "Could not rebuild project"

./wsjcpp uninstall example-wsjcpp-package-localfs
check_ret $? "problem with uninstall example-wsjcpp-package-localfs"
if [ -d $EXPECTED_DIR ]; then
    echo "Found directory "$EXPECTED_DIR
    exit 1
fi