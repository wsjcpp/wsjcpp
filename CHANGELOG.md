# wsjcpp changelog

## v0.1.6 - 2020 Sept 4

* Implemented 'wsjcpp res rm %dir%' and normalized path in resources add './' for every resource
* Implemented 'wsjcpp res add %dir%'
* Improved output error for 'wsjcpp res add'
* Allow create ut without description && improved short commands
* Updated version to 0.1.6
* Prepare new subcommand 'wsjcpp scan uniq-lines'
* Added test for install from localfs
* Fixed origin for localfs packages
* Fixed  #44 added installation from localfs
* Fixed example
* Removed unuseful script install.sh
* Added test for installation from https
* Redesign installation from http(s) packages
* Replaced WsjcppCore::listOfFiles -> WsjcppCore::getListOfFiles
* Fixed TODO remove cache folder if could not download
* Updated wsjcpp-arguments:v0.2.0
* Fixed TODO
* Updated wsjcpp-core:v0.1.7
* Fixed #53 short command for 'wsjcpp unit-tests list' -> 'wsjcpp ut ls'