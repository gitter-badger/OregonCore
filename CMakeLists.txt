# This file is part of the OregonCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Set projectname (must be done AFTER setting configurationtypes)
project(OregonCore)
cmake_minimum_required(VERSION 2.8)

# cmake policies, cannot be handled elsewhere
# run cmake --help-policy CMPxxxx for details
# note: I tried to use macro for this, but didnt work
IF (POLICY CMP0005)
    cmake_policy(SET CMP0005 NEW)
ENDIF()
IF (POLICY CMP0043)
    cmake_policy(SET CMP0043 OLD)
ENDIF()
IF (POLICY CMP0053)
    cmake_policy(SET CMP0053 OLD)
ENDIF()
IF (POLICY CMP0054)
    cmake_policy(SET CMP0054 OLD)
ENDIF()

# Set RPATH-handing (CMake parameters)
set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# build in preferred mode
if( NOT CMAKE_BUILD_TYPE )
    if (WITH_COREDEBUG)
        set(CMAKE_BUILD_TYPE "Debug")
    else()
        set(CMAKE_BUILD_TYPE "Release")
    endif()
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# set default buildoptions and print them
include(cmake/options.cmake)

# turn off PCH totally if enabled (hidden setting, mainly for devs)
if( NOPCH )
  set(USE_COREPCH 0)
  set(USE_SCRIPTPCH 0)
endif()

include(CheckPlatform)

# basic packagesearching and setup (further support will be needed, this is a preliminary release!)
find_package(PCHSupport)
find_package(ACE REQUIRED)
find_package(OpenSSL REQUIRED)
if( NOT USE_MYSQL_SOURCES )
  find_package(MySQL REQUIRED)
endif()

if( UNIX )
  find_package(Curses)
  find_package(ZLIB)
  find_package(BZip2)
  find_package(Binutils)
endif()

# Find revision ID and hash of the sourcetree
include(cmake/genrev.cmake)

if ( WITH_DOCS )
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(
          "${CMAKE_SOURCE_DIR}/Doxyfile.in.cmake"
          "${CMAKE_BINARY_DIR}/Doxyfile"
          @ONLY)
        add_custom_target(docs
          ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen" VERBATIM)
        install(DIRECTORY ${CMAKE_BINARY_DIR}/doc DESTINATION .)
    else()
        set(WITH_DOCS 0)
    endif()
endif()

# print out the results before continuing
include(cmake/showoptions.cmake)

# add dependencies
add_subdirectory(dep)

# add core sources
add_subdirectory(src)
