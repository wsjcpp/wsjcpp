cmake_minimum_required(VERSION 3.0)

project(wsjcpp)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_INCLUDE_DIRS "src/ArgumentsProcessors")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_install.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_install.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_run.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_run.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_unit_tests.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_templates.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_templates.h")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.cpp")
list (APPEND WSJCPP_SOURCES "src/ArgumentsProcessors/argument_processor_main.h")

list (APPEND WSJCPP_SOURCES "src/main.cpp")

# LIBZIP
if(MACOSX)  # TODO redesign
  set(LIBZIP_INCLUDE_DIRS "/usr/local/Cellar/libzip/1.5.2/include/")
  list (APPEND WSJCPP_INCLUDE_DIRS ${LIBZIP_INCLUDE_DIRS})
  set(LIBZIP_LIBRARIES "/usr/local/Cellar/libzip/1.5.2/lib/libzip.dylib")
  list (APPEND WSJCPP_LIBRARIES ${LIBZIP_LIBRARIES})
else(MACOSX)
  
set(LIBZIP_INCLUDE_DIRS "/usr/include/")
list (APPEND WSJCPP_INCLUDE_DIRS ${LIBZIP_INCLUDE_DIRS})
set(LIBZIP_LIBRARIES "/usr/lib/x86_64-linux-gnu/libzip.so")
list (APPEND WSJCPP_LIBRARIES ${LIBZIP_LIBRARIES})
  
endif(MACOSX)

# ZLIB
FIND_PACKAGE(ZLIB REQUIRED)
IF(ZLIB_FOUND)
    list (APPEND WSJCPP_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    list (APPEND WSJCPP_LIBRARIES ${ZLIB_LIBRARIES})
ELSE(ZLIB_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the zlib library and development files.")
endif( ZLIB_FOUND )

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        wsjcpp
    RUNTIME DESTINATION
        /usr/bin
)
