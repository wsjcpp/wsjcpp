# ChangeLog

All notable changes to wsjcpp project will be documented in this file.
 
The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [v0.2.2] - 2021-??-?? (2021 ?? ??)

### Added

- Added new 'wsjcpp unit-tests run' or short 'wsjcpp ut r'

## [v0.2.1] - 2021-04-11 (2021 Apr 11)

### Added

- added short for 'update' -> 'up'

### Fixed

- Don't create .gitkeep file in src.wsjcpp (not need)

## [v0.2.0] - 2020-10-18 (2020 Oct 18)

### Added

- Fixed #82: Add 'wsjcpp prepare changelog'
- Prepare single argumets --text, --json, --html  for 'wsjcpp scan' #48
- Fixed #75: add new field 'installation-datetime' to dependence information
- Fixed #76. Implemented feature: write file VERSION if it enabled.
- Added new author of project: Danil Dudkin
- Added auto detection file type on 'wsjcpp dist add'
- Fixed #22 added validate version format like 'v0.0.0'
- Fixed #57 implemented command 'wsjcpp chnage version %vers%'

### Changed

- Moved main.cpp to src/app
- Improve command 'wsjcpp dist add <dir/file>'
- No dependencies - no create folder src.wsjcpp and no updates for src.wsjcpp/CMakeLists.txt
- No create unit-tests.wsjcpp folder if it hasn't define unit-tests
- Fixed #72 Redesign unit-tests create
- Improved remove resource
- Redesign generate resources

### Removed

- Removed section 'cmake/install' from unit-tests/CMakeLists.txt 
- Removed unused files

### Fixed

- bug: After remove last resource node - will removed node 'resources:' in wsjcpp.yml
- Fixed #61 Cleanup main function
- Fixed #83 bug with WsjcppPackageManager::validateVersionFormat
- Fixed  #62: Build error after init
- Collect 'required-libraries' from dependencies
- Fixed normalized path
- Fixed wsjcpp reinstall
- Fixed #73 reinstall package from github
- Fixed unit-tests after update wsjcpp-core

### Security

- Updated wsjcpp-arguments to v0.2.1
- Updated wsjcpp-yaml to v0.1.5
- Integrated with lgtm
- Updated wsjcpp-core to v0.2.0

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