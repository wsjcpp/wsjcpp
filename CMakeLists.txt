cmake_minimum_required(VERSION 3.0)

project(cppspm)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.cppspm/CMakeLists.txt)

# set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${cppspm_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND CPPSPM_INCLUDE_DIRS "src")

list (APPEND CPPSPM_SOURCES "src/cppspm_author.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_author.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_server.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_server.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_dependence.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_dependence.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_download_dependence.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_download_dependence.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_file.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_file.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_repository.h")
list (APPEND CPPSPM_SOURCES "src/cppspm_repository.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_manager.cpp")
list (APPEND CPPSPM_SOURCES "src/cppspm_manager.h")
list (APPEND CPPSPM_SOURCES "src/main.cpp")

# ZLIB
find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    list (APPEND CPPSPM_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    list (APPEND CPPSPM_LIBRARIES ${ZLIB_LIBRARIES})
endif( ZLIB_FOUND )

# CURL
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  list (APPEND CPPSPM_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
  list (APPEND CPPSPM_LIBRARIES ${CURL_LIBRARIES})
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

include_directories(${CPPSPM_INCLUDE_DIRS})

add_executable (cppspm ${CPPSPM_SOURCES})

target_link_libraries(cppspm -lpthread ${CPPSPM_LIBRARIES} )

install(
    TARGETS
        cppspm
    RUNTIME DESTINATION
        /usr/bin
)
