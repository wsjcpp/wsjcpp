# wsjcpp

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp) [![Docker Pulls](https://img.shields.io/docker/pulls/sea5kg/wsjcpp.svg)](https://hub.docker.com/r/sea5kg/wsjcpp/) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp.svg)](https://github.com/wsjcpp/wsjcpp) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp/network/members)

Yet one... C++ Source Package Manager

## Build and Install

### MacOS (Build and Install)

Short list commands:
```
$ brew install curl-openssl pkg-config cmake
$ cd ~
$ git clone https://github.com/wsjcpp/wsjcpp
$ cd ~/wsjcpp
$ ./build_simple.sh
$ sudo ln -s `pwd`/wsjcpp /usr/local/bin/wsjcpp
```

### Ubuntu/Debian (Build and Install)

Short list commands:
```
$ sudo apt install cmake make g++ pkg-config libcurl4-openssl-dev git-core
$ cd ~
$ git clone https://github.com/wsjcpp/wsjcpp
$ cd ~/wsjcpp
$ ./build_simple.sh
$ sudo ln -s `pwd`/wsjcpp /usr/local/bin/wsjcpp
```

## Init new package

```
$ cd your_package
$ wsjcpp new .
```

Will be prepared file: CMakeLists.txt

For distribute your files:

```
$ wsjcpp distribution add src/your_source_file.cpp
```

## How to install packages

From github:

```
$ wsjcpp install 'https://github.com/sea-kg/nlohmann_json:v3.7.0'
```

From bitbucket (not implemented yet):
```
$ wsjcpp install https://bitbucket.org/sea-kg/nlohmann_json:v3.7.0
```

Via (http/https) link (not implemented yet):
```
$ wsjcpp install https://sea-kg.com/wsjcpp/pkg-example/v1.0.0
$ wsjcpp install http://sea-kg.com/wsjcpp/pkg-example/v1.0.0
```

From local folder:
```
$ wsjcpp install file:///usr/share/pkg-example-v1.0.0
```

## How to look what packages installed

`$ wsjcpp list`

Example
```
$ wsjcpp list
Dependencies: 
* 'wsjcpp-core:v0.0.4' (https://github.com/wsjcpp/wsjcpp-core:master -> ./src.wsjcpp/wsjcpp_core)
* 'wsjcpp-yaml:v0.0.2' (https://github.com/wsjcpp/wsjcpp-yaml:master -> ./src.wsjcpp/wsjcpp_yaml)
* 'wsjcpp/wsjcpp-arguments:v0.0.1' (https://github.com/wsjcpp/wsjcpp-arguments:master -> ./src.wsjcpp/wsjcpp_wsjcpp_arguments)
* 'wsjcpp/wsjcpp-hashes:v0.0.1' (https://github.com/wsjcpp/wsjcpp-hashes:master -> ./src.wsjcpp/wsjcpp_wsjcpp_hashes)
```

## How to uninstall packages

```
$ wsjcpp uninstall 'sea-kg/nlohmann_json'
```

## Infomation about package 

```
$ wsjcpp info 'sea-kg/nlohmann_json'
```

About current package:

```
$ wsjcpp info
```


### Build and run in docker

Build:

```
$ docker build --rm --tag "wsjcpp" .
$ sudo docker run -it --rm \
  -v `pwd`/.:/home/node/app \
  -w /home/node/app \
  angular-cli-start:latest \
  bash
```

Run:

```
$ sudo docker run -it --rm \
  -v `pwd`/.:/root/project \
  wsjcpp:latest \
  bash
```