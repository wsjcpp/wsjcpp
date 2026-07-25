##################################################################################
#
# MIT License
#
# Copyright (c) 2019-2026 Evgenii Sopov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# original source-code: https://github.com/wsjcpp/wsjcpp
#
##################################################################################

cmake_minimum_required(VERSION 3.5)

project(wsjcpp)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

#### BEGIN_WSJCPP_APPEND
#### END_WSJCPP_APPEND

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_INCLUDE_DIRS "src/ArgumentsProcessors")


list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_author.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_author.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_dependence.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_dependence.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_distribution_file.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_distribution_file.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_resource_file.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_resource_file.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_safe_scripting_generate.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_safe_scripting_generate.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.h")

list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_base.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_base.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_bitbucket.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_bitbucket.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_github.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_github.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_gitlab.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_gitlab.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_http.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_http.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_localfs.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloader_localfs.cpp")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloaders.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_package_downloaders.cpp")

list (APPEND WSJCPP_SOURCES "src/third_party/smallsha1/smallsha1.cpp")
list (APPEND WSJCPP_SOURCES "src/s5k/main.cpp")
list (APPEND WSJCPP_SOURCES "src/s5k/utils/s5k_helpers.cpp")

list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_dependencies.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_dependencies.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_distribution.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_distribution.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_run.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_run.h")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_scan.h")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_scan.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_unit_tests.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_generate.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_generate.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_change.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_change.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_basic.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_basic.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_origins.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_origins.cpp")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_prepare.h")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_prepare.cpp")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_resources.h")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_resources.cpp")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_authors.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_lint.cpp")


include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        wsjcpp
    RUNTIME DESTINATION
        /usr/local/bin
)

# enable testing functionality
enable_testing()
add_subdirectory(src/tests)
