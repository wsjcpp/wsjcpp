# cppspm

(in process)

C++ Source Package Manager

## Build && Develop

### Mac OS

Requirements:
```
$ brew install libzip
$ ./build_simple.sh
```


### Ubuntu/Debian

Compile and install (just a copy cppspm to /usr/bin/)
```
$ sudo apt install libzip-dev 
$ ./build_simple.sh
$ ./install.sh
```

## Init new package

```
$ cd your_package
$ cppspm new .
```

For distribute files:

```
$ cppspm add-file src/your_source_file.cpp
```

## Run local server

```
$ cppspm --port 3001 --datadir ./data start-server
```

## Install requirements

From github:

```
$ cppspm install https://github.com/sea-kg/nlohmann_json:v3.7.0
```

From bitbucket:
```
$ cppspm install https://bitbucket.org/sea-kg/nlohmann_json:v3.7.0
```

Via link:
```
$ cppspm install https://sea-kg.com/cppspm/somepkg-v1.0.0.zip
$ cppspm install http://sea-kg.com/cppspm/somepkg-v1.0.0.zip
```

from cppspm servers:
```
$ cppspm install cppspm/somepkg-v1.0.0.zip
```

