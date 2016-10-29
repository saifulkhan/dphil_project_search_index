##############################################################################################
# CMakeList
# Common
##############################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
PROJECT(Common)

#
# Compiler flags
#

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


##############################################################################################
## Sources path (cpp/h)
## Install path
## List of Source: cpp, h, conf files to be built ##
##############################################################################################
FILE(GLOB_RECURSE MY_SOURCE_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/Conversion.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/DateTime.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/FileInfo.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/FileTypes.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Random.cpp")

FILE(GLOB_RECURSE MY_INCLUDE_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/Conversion.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Algorithm.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/DateTime.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/FileInfo.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/FileTypes.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Random.h")

FILE(GLOB_RECURSE MY_CONF_FILES "${CMAKE_CURRENT_SOURCE_DIR}/conf/FileTypes.xml")

#
# Target/Install path
#
set(MY_INSTALL_LIBRARY_PATH  "${CMAKE_INSTALL_PREFIX}/lib")
set(MY_INSTALL_INCLUDE_PATH  "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
set(MY_INSTALL_CONF_PATH "${CMAKE_INSTALL_PREFIX}/conf/")

##############################################################################################
## Define variables 
## Used in C++ as #define ..
##############################################################################################
add_definitions(-DFILE_TYPES_XML="${MY_INSTALL_CONF_PATH}/FileTypes.xml")


##############################################################################################
## Build
## Include my header files, required to build the cpp files
## The Wordnet files are dependent on common so as common files on Wordnet, 
## they can find even if included locally using ""
## shared build, therefore, my header files only required
##############################################################################################
 INCLUDE_DIRECTORIES(${MY_INCLUDE_FILES})

## Build shared library ##
ADD_DEFINITIONS(-DLPP_BUILDING_LIB)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${MY_SOURCE_FILES})


#
# Install
#
INSTALL(FILES ${MY_INCLUDE_FILES} DESTINATION ${MY_INSTALL_INCLUDE_PATH})  # .h files
install(TARGETS ${PROJECT_NAME} DESTINATION ${MY_INSTALL_LIBRARY_PATH})	  # libCommon.so
install(FILES ${MY_DICT_FILES} DESTINATION ${MY_INSTALL_DICT_PATH})
install(FILES ${MY_CONF_FILES} DESTINATION ${MY_INSTALL_CONF_PATH})


##############################################################################################
## Test ##
## Process subdirectoryies here, Test binary ##
##############################################################################################
enable_testing()
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/test")


##############################################################################################
## Debug messages ##
##############################################################################################
message("** Build Summary **")
message(" Version:        ${Commom_VERSION}")
message(" Install Prefix:${CMAKE_INSTALL_PREFIX}")
message(" Build Type:     ${CMAKE_BUILD_TYPE}")
message(" Architecture|System :   ${CMAKE_SYSTEM_PROCESSOR} | ${CMAKE_SYSTEM_NAME}")
message(" SourcePath Source|Include|Conf: ${MY_SOURCE_FILES} | ${MY_INCLUDE_FILES} | ${MY_CONF_FILES}")
message(" Install Include|Library|Conf:   ${MY_INSTALL_INCLUDE_PATH} | ${MY_INSTALL_LIBRARY_PATH} | ${MY_INSTALL_CONF_PATH}")
