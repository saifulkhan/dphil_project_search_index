# Install script for directory: /home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/saiful/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/saiful/install/include/Index/stdHeader.h;/home/saiful/install/include/Index/Index.h;/home/saiful/install/include/Index/Document.h;/home/saiful/install/include/Index/IndexMerge.h;/home/saiful/install/include/Index/SegmentInfos.h;/home/saiful/install/include/Index/HitDoc.h;/home/saiful/install/include/Index/IndexReader.h;/home/saiful/install/include/Index/IndexSearch.h;/home/saiful/install/include/Index/PriQueue.h;/home/saiful/install/include/Index/IndexOutput.h;/home/saiful/install/include/Index/IndexInput.h;/home/saiful/install/include/Index/IndexWriter.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/saiful/install/include/Index" TYPE FILE FILES
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/stdHeader.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Index.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Document/Document.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Merge/IndexMerge.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Merge/SegmentInfos.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Reader/HitDoc.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Reader/IndexReader.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Search/IndexSearch.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Search/PriQueue.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Store/IndexOutput.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Store/IndexInput.h"
    "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Writer/IndexWriter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/saiful/install/lib/libIndex.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/saiful/install/lib" TYPE SHARED_LIBRARY FILES "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/libIndex.so")
  IF(EXISTS "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/saiful/install/lib/libIndex.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/Analyser/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/saiful/git-code/Enterprise-Search-Engine/Inverted-Index/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
