## CMakeList ##
## QueryProcessor    ##

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(QueryProcessor)


## Compiler flags ##

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")



##############################################################################################
## Sources path (cpp/h)
## Install path
## List of Source: cpp, h, conf files to be built ##
##############################################################################################
FILE(GLOB_RECURSE MY_SOURCE_FILES   "${CMAKE_CURRENT_SOURCE_DIR}/QueryProcessor.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Term.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/QueryParser.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/MachineLearning/*.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Treemap/*.cpp")

FILE(GLOB_RECURSE MY_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/QueryProcessor.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Term.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/QueryParser.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/MachineLearning/*.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Treemap/*.h")

## Target/Install path##

set(MY_INSTALL_LIBRARY_PATH  "${CMAKE_INSTALL_PREFIX}/lib")
set(MY_INSTALL_INCLUDE_PATH  "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")

##############################################################################################
## Define variables
## Used in C++ as #define ..
##############################################################################################

add_definitions(-DJSON_TREEMAP_DEPTH="3")
add_definitions(-DBORDER_WIDTH="8")

##############################################################################################
## Build
## Include my header files required to build
## shared build, therefore, my header files only required
##############################################################################################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
                    "${CMAKE_CURRENT_SOURCE_DIR}/MachineLearning"
                    "${CMAKE_CURRENT_SOURCE_DIR}/Treemap"
                    # + Depends on Ontology, Common, Index, & LanguageProcessor
                    "${CMAKE_INSTALL_PREFIX}/include/Ontology"
                    "${CMAKE_INSTALL_PREFIX}/include/Common"
                    "${CMAKE_INSTALL_PREFIX}/include/Index"
                    "${CMAKE_INSTALL_PREFIX}/include/LanguageProcessor")

## Build shared library ##
ADD_DEFINITIONS(-DLPP_BUILDING_LIB)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${MY_SOURCE_FILES})

## Install ##
INSTALL(FILES ${MY_INCLUDE_FILES} DESTINATION ${MY_INSTALL_INCLUDE_PATH})  # .h files
install(TARGETS ${PROJECT_NAME} DESTINATION ${MY_INSTALL_LIBRARY_PATH})	   # libIndex.so


##############################################################################################
## Test ##
## Process subdirectoryies here, Test binary ##
##############################################################################################
enable_testing()
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Test")

## Debug messages ##

##############################################################################################
## Debug messages ##
##############################################################################################
message("** Build Summary **")
message(" Version:        ${Commom_VERSION}")
message(" Install Prefix:${CMAKE_INSTALL_PREFIX}")
message(" Build Type:     ${CMAKE_BUILD_TYPE}")
message(" Architecture|System :   ${CMAKE_SYSTEM_PROCESSOR} | ${CMAKE_SYSTEM_NAME}")
message(" Boost Include|Library:  ${Boost_INCLUDE_DIRS} | ${Boost_LIBRARY_DIRS}")
message(" SourcePath Source|Include: ${MY_SOURCE_FILES} | ${MY_INCLUDE_FILES}")
message(" Install Include|Library:   ${MY_INSTALL_INCLUDE_PATH} | ${MY_INSTALL_LIBRARY_PATH}")
