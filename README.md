# cppspm

(in process)

C++ Source Package Manager


## Installation

(Ubuntu/Debian)

Compile and install (just a copy cppspm to /usr/bin/)
```
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