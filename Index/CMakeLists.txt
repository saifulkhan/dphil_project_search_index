## CMakeList ##
## Index    ##

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(Index)


#
# Compiler flags
#
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


##############################################################################################
## Sources path (cpp/h)
## Install path
## List of Source: cpp, h, conf files to be built ##
##############################################################################################
FILE(GLOB_RECURSE MY_SOURCE_FILES   "${CMAKE_CURRENT_SOURCE_DIR}/Index.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Document/Document.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Merge/IndexMerge.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Merge/SegmentInfos.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Reader/HitDoc.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Reader/IndexReader.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Search/IndexSearch.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Search/PriQueue.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Store/IndexOutput.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Store/IndexInput.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Writer/IndexWriter.cpp")

FILE(GLOB_RECURSE MY_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/stdHeader.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Index.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Document/Document.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Merge/IndexMerge.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Merge/SegmentInfos.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Reader/HitDoc.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Reader/IndexReader.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Search/IndexSearch.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Search/PriQueue.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Store/IndexOutput.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Store/IndexInput.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Writer/IndexWriter.h")
#
# Target/Install path
#
set(MY_INSTALL_LIBRARY_PATH  "${CMAKE_INSTALL_PREFIX}/lib")
set(MY_INSTALL_INCLUDE_PATH  "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")


##############################################################################################
## Define variables
## Used in C++ as #define ..
##############################################################################################
add_definitions(-DDIR_CACHE_PATH="${CMAKE_INSTALL_PREFIX}/index/")


##############################################################################################
## Build
## Include my header files required to build
## shared build, therefore, my header files only required
## NOTE: All directories are given here to resolve the header call from different directory. e.g.,
## - in Index.h can call "IndexInput.h" directly
##############################################################################################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
                    "${CMAKE_CURRENT_SOURCE_DIR}/Document"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Merge"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Reader"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Search"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Store"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Writer"
                    # Depends on Common, LanguageProcessor lib, so include the header to resolve defn.
                    "${CMAKE_INSTALL_PREFIX}/include/Common"
                    "${CMAKE_INSTALL_PREFIX}/include/LanguageProcessor")



#
# Build shared library
#
ADD_DEFINITIONS(-DLPP_BUILDING_LIB)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${MY_SOURCE_FILES})

#
# Install
#
INSTALL(FILES ${MY_INCLUDE_FILES} DESTINATION ${MY_INSTALL_INCLUDE_PATH})  # .h files
install(TARGETS ${PROJECT_NAME} DESTINATION ${MY_INSTALL_LIBRARY_PATH})	   # libIndex.so


##############################################################################################
## Test ##
## Process subdirectoryies here, Test binary ##
##############################################################################################
enable_testing()
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Analyser")

## Debug messages ##

##############################################################################################
## Debug messages ##
##############################################################################################
message("** Build Summary **")
#message(" Version:        ${Commom_VERSION}")
message(" Install Prefix:${CMAKE_INSTALL_PREFIX}")
message(" Build Type:     ${CMAKE_BUILD_TYPE}")
message(" Architecture|System :   ${CMAKE_SYSTEM_PROCESSOR} | ${CMAKE_SYSTEM_NAME}")
message(" Boost Include|Library:  ${Boost_INCLUDE_DIRS} | ${Boost_LIBRARY_DIRS}")
message(" SourcePath Source|Include: ${MY_SOURCE_FILES} | ${MY_INCLUDE_FILES}")
message(" Install Include|Library:   ${MY_INSTALL_INCLUDE_PATH} | ${MY_INSTALL_LIBRARY_PATH}")
