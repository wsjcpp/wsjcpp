cmake_minimum_required(VERSION 3.0)

project(wsjcpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_server.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_server.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_dependence.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_dependence.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_download_dependence.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_download_dependence.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_file.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_file.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_repository.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_repository.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_package_manager.h")
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

# CURL
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  list (APPEND WSJCPP_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
  list (APPEND WSJCPP_LIBRARIES ${CURL_LIBRARIES})
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp -lpthread ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        wsjcpp
    RUNTIME DESTINATION
        /usr/bin
)
