#!/bin/bash

if [ $1 == "clean" ]; then
    # if docker images exists todo remove it
fi

if [ $1 == "build" ]; then
    # prepare docker.for-build
    cd docker.for-build
    docker build .
    cd ..
    docker run -d -v "./:/root/sources" wsjcpp-for-build:latest "/usr/bash -c 'mkdir -p tmp.docker && cd tmp.docker && cmake .. && make'"
fi

if [ $1 == "release" ]; then
    # prepare docker.for-build
    cd docker.for-build
    docker build .
    cd ..
    # prepare docker.for-release
    cd docker.for-release
    docker build .
    cd ..
    # build docker in parent directory
    docker build -f Dockerfile
fi



docker build -f Dockerfile.build
docker build -f Dockerfile.release
docker build -f Dockerfile