cmake_minimum_required(VERSION 3.0)

project(wsjcpp)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

#### BEGIN_WSJCPP_APPEND
#### END_WSJCPP_APPEND

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_INCLUDE_DIRS "src/ArgumentsProcessors")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_distribution_file.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_distribution_file.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_safe_scripting_generate.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager_safe_scripting_generate.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.h")

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
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_basic.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_basic.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_origins.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_origins.cpp")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_prepare.h")
list (APPEND WSJCPP_SOURCES "./src/ArgumentsProcessors/argument_processor_prepare.cpp")

list (APPEND WSJCPP_SOURCES "src/main.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        wsjcpp
    RUNTIME DESTINATION
        /usr/local/bin
)


