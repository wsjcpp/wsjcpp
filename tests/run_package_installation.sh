#!/bin/bash

cd ..
./wsjcpp install https://wsjcpp.org/packages/example-wsjcpp-package-https/v0.0.1/
./build_simple.sh
EXPECTED_DIR="./src.wsjcpp/example_wsjcpp_package_https"
if [ ! -d $EXPECTED_DIR ]; then
    echo "Not found dir "$EXPECTED_DIR
    exit 1
fi

./wsjcpp uninstall https://wsjcpp.org/packages/example-wsjcpp-package-https/v0.0.1/
if [ -d $EXPECTED_DIR ]; then
    echo "Found directory "$EXPECTED_DIR
    exit 1
fi