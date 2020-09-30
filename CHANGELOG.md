# ChangeLog

All notable changes to wsjcpp project will be documented in this file.
 
The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [v0.2.0] - ??

### Changed

- Updated CHANGELOG.md

### Fixed

- bug: After remove last resource node - will removed node 'resources:' in wsjcpp.yml


## [v0.1.6] - 2020-09-04 (2020 Sept 4)

### Added

- Fixed #53 short command for 'wsjcpp unit-tests list' -> 'wsjcpp ut ls'
- Implemented 'wsjcpp res rm %dir%' and normalized path in resources add './' for every resource
- Implemented 'wsjcpp res add %dir%'
- Fixed  #44 added installation from localfs
- Prepare new subcommand 'wsjcpp scan uniq-lines'
- Added test for install from localfs
- Added test for installation from https

### Changed

- Updated version to 0.1.6
- Improved output error for 'wsjcpp res add'
- Redesign installation from http(s) packages

### Deprecated

Nope

### Removed

- Removed unuseful script install.sh

### Fixed

- Fixed TODO remove cache folder if could not download
- Fixed TODOs
- Fixed examples
- Fixed origin for localfs packages
- Replaced WsjcppCore::listOfFiles -> WsjcppCore::getListOfFiles
- Allow create ut without description && improved short commands

### Security

- Updated wsjcpp-arguments:v0.2.0
- Updated wsjcpp-core:v0.1.7