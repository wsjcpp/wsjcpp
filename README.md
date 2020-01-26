# wsjcpp

Yet one... C++ Source Package Manager

## Build and Install

* [Build && Install: Mac OS](https://github.com/sea-kg/wsjcpp/blob/master/docs/BUILD-AND-INSTALL-MACOS.md)
* [Build && Install: Ubuntu/Debian](https://github.com/sea-kg/wsjcpp/blob/master/docs/BUILD-AND-INSTALL-UBUNTU.md)

## Init new package

```
$ cd your_package
$ wsjcpp new .
```

Will be prepared file: CMakeLists.txt

For distribute your files:

```
$ wsjcpp files add src/your_source_file.cpp
```

## How to install packages

From github:

```
$ wsjcpp install 'https://github.com/sea-kg/nlohmann_json:v3.7.0'
```

From bitbucket:
```
$ wsjcpp install https://bitbucket.org/sea-kg/nlohmann_json:v3.7.0
```

Via link:
```
$ wsjcpp install https://sea-kg.com/wsjcpp/pkg-example/v1.0.0
$ wsjcpp install http://sea-kg.com/wsjcpp/pkg-example/v1.0.0
```

From local folder:
```
$ wsjcpp install file:///usr/share/pkg-example-v1.0.0
```

## How to look what installed

```
$ wsjcpp deps list
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