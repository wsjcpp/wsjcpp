# wsjcpp

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Docker Pulls](https://img.shields.io/docker/pulls/sea5kg/wsjcpp.svg)](https://hub.docker.com/r/sea5kg/wsjcpp/) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp.svg)](https://github.com/wsjcpp/wsjcpp) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp/context:cpp) [![deepcode](https://www.deepcode.ai/api/gh/badge?key=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJwbGF0Zm9ybTEiOiJnaCIsIm93bmVyMSI6IndzamNwcCIsInJlcG8xIjoid3NqY3BwIiwiaW5jbHVkZUxpbnQiOmZhbHNlLCJhdXRob3JJZCI6MTU2NDEsImlhdCI6MTYxODcxNzM1M30.tYld0fGXb1L2UDJt5oJwodBlzDOsfGNSk_121jug4Vg)](https://www.deepcode.ai/app/gh/wsjcpp/wsjcpp/_/dashboard?utm_content=gh%2Fwsjcpp%2Fwsjcpp)

Yet another... C++ Source Package Manager

Official site: [https://wsjcpp.org/](https://wsjcpp.org/)

## Get for work 


### Use a docker

Docker:
```
$ docker pull sea5kg/wsjcpp:latest
$ docker run -it --rm \
    -v `pwd`/.:/root/project \
    sea5kg/wsjcpp:latest \
    bash
root@8b93098b8a07:~/project#
```
Now you can call wsjcpp inside a container
For exit, just enter `exit` command after this container will be destroed.

### Install to MacOS

```
$ brew tap wsjcpp/wsjcpp
$ brew install wsjcpp
```

### Install on Ubuntu from ppa

```
$ sudo add-apt-repository ppa:sea5kg/wsjcpp
$ sudo apt-get update
$ sudo apt-get install wsjcpp
```

### Build and install in Ubuntu/Debian

```
$ sudo apt install cmake make g++ pkg-config libcurl4-openssl-dev git-core
$ git clone https://github.com/wsjcpp/wsjcpp /tmp/wsjcpp.git
$ cd /tmp/wsjcpp.git
$ ./build_simple.sh
$ sudo cp -r /tmp/wsjcpp.git /bin/wsjcpp
```

## More package managers for c++

[Here](https://github.com/wsjcpp/wsjcpp/blob/master/docs/PACKAGE_MANAGERS_FOR_CPP.md)

## Basic usage

### Init new project / package

Inside with your folder project
```
$ wsjcpp init .
$ chmod +x build_simple.sh
$ chmod +x unit-tests.wsjcpp/build_simple.sh
```

If you already have a project and want integrate to you project please look here: TODO

On this step will be generated different files, like (only if files not exists):

- src.wsjcpp/CMakeLists.txt
- src.wsjcpp/wsjcpp_core/* <- sample of package (core always required)
- unit-tests.wsjcpp/* <- folder for unit-tests
- src/main.cpp
- .wsjcpp/* <- temporary folder
- CMakeLists.txt
- build_simple.sh
- .gitignore
- ...

### Install packages

You can find on github package what a need you here (for example) https://github.com/topics/wsjcpp

And next command you can install package:
```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-print-tree:master
```
Also you can change 'master' to specific version or branch

After downloading wsjcpp will be automaticly update file: src.wsjcpp/CMakeLists.txt

### Upgrade package

```
$ wsjcpp list 

  Dependencies: 
  * 'wsjcpp-core:v0.0.8' (https://github.com/wsjcpp/wsjcpp-core:master -> ./src.wsjcpp/wsjcpp_core)
  * 'wsjcpp-print-tree:v0.0.1' (https://github.com/wsjcpp/wsjcpp-print-tree:master -> ./src.wsjcpp/wsjcpp_print_tree)

$ wsjcpp reinstall wsjcpp-print-tree
```

### Uninstall package

```
$ wsjcpp uninstall https://github.com/wsjcpp/wsjcpp-print-tree:master
```

## Unit-tests

Create a new unit-test
```
$ wsjcpp unit-tests create SomeTest "Tesing some"
```
Will be created new files:

- unit-tests.wsjcpp/src/unit_test_init_package.h
- unit-tests.wsjcpp/src/unit_test_init_package.cpp

Also will be automaticly updated unit-tests.wsjcpp/CMakeLists.txt

For build and run unit-tests:
```
$ cd unit-tests.wsjcpp
$ ./build_simple.sh
$ ./unit-tests
```

P.S. For testing you package - you need define distribution files (for automaticly include to unit-tests.wsjcpp/CMakeLists.txt)

## Specify distribution files from your package for uses your package

### Add to distribution
```
$ wsjcpp distribution add src/your_source_file.h
$ wsjcpp distribution add src/your_source_file.cpp
```

Will be updated section 'distribution' in wsjcpp.yml
```
distribution:
  - source-file: "src/your_source_file.h"
    target-file: "your_source_file.h"
    type: "source-code"
  - source-file: "src/your_source_file.cpp"
    target-file: "your_source_file.cpp"
    type: "source-code"
```

### Remove from distribution
```
$ wsjcpp distribution remove src/your_source_file.cpp
```

## Manual changed wsjcpp.yml

For update automaticly generated files:
```
$ wsjcpp update
```


## For building 

wsjcpp prepare file 'build_simple.sh' for easy building 
```
$ ./build_simple.sh
```