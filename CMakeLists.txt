cmake_minimum_required(VERSION 3.0)

project(cppspm)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/src.cppspm/CMakeLists.txt)

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

# LIBZIP
if(MACOSX)  # TODO redesign
  set(LIBZIP_INCLUDE_DIRS "/usr/local/Cellar/libzip/1.5.2/include/")
  list (APPEND CPPSPM_INCLUDE_DIRS ${LIBZIP_INCLUDE_DIRS})
  set(LIBZIP_LIBRARIES "/usr/local/Cellar/libzip/1.5.2/lib/libzip.dylib")
  list (APPEND CPPSPM_LIBRARIES ${LIBZIP_LIBRARIES})
else(MACOSX)
  find_package(LIBZIP REQUIRED)
  if(LIBZIP_FOUND)
      list (APPEND CPPSPM_INCLUDE_DIRS ${LIBZIP_INCLUDE_DIRS})
      list (APPEND CPPSPM_LIBRARIES ${LIBZIP_LIBRARIES})
  else(LIBZIP_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the libzip library and development files.")
  endif( LIBZIP_FOUND )
endif(MACOSX)

# ZLIB
FIND_PACKAGE(ZLIB REQUIRED)
IF(ZLIB_FOUND)
    list (APPEND CPPSPM_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    list (APPEND CPPSPM_LIBRARIES ${ZLIB_LIBRARIES})
ELSE(ZLIB_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the zlib library and development files.")
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
