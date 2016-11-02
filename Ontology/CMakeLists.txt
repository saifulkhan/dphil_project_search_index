## CMakeList ##
 
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(Ontology)


## Compiler flags ##

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")



##############################################################################################
## Sources path (cpp/h)
## Install path
## List of Source: cpp, h, conf files to be built ##
##############################################################################################
FILE(GLOB_RECURSE MY_SOURCE_FILES   "${CMAKE_CURRENT_SOURCE_DIR}/OntologyFactory.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Ontology.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/TypeOntology.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/TermOntology.cpp"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/SizeOntology.cpp")

FILE(GLOB_RECURSE MY_INCLUDE_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/OntologyFactory.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/Ontology.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/TypeOntology.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/TermOntology.h"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/SizeOntology.h")

FILE(GLOB_RECURSE MY_CONF_FILES    "${CMAKE_CURRENT_SOURCE_DIR}/License/Configuration.cfg")

## Target/Install path ##

set(MY_INSTALL_LIBRARY_PATH  "${CMAKE_INSTALL_PREFIX}/lib")
set(MY_INSTALL_INCLUDE_PATH  "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
set(MY_INSTALL_CONF_PATH "${CMAKE_INSTALL_PREFIX}/conf/")


##############################################################################################
## Define variables
## Used in C++ as #define ..
##############################################################################################

add_definitions(-DGDB_CFG="${CMAKE_INSTALL_PREFIX}/conf/Configuration.cfg")
add_definitions(-DTERM_ONTOLOGY="${CMAKE_INSTALL_PREFIX}/gdb/TermOntology.gdb")
add_definitions(-DTYPE_ONTOLOGY="${CMAKE_INSTALL_PREFIX}/gdb/TypeOntology.gdb")
add_definitions(-DSIZE_ONTOLOGY="${CMAKE_INSTALL_PREFIX}/gdb/SizeOntology.gdb")


##############################################################################################
## Build
## Include my header files required to build
## shared build, therefore, my header files only required
##############################################################################################

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
                    "${CMAKE_INSTALL_PREFIX}/include/Common"
                    "${CMAKE_INSTALL_PREFIX}/include/LanguageProcessor"
                    "${CMAKE_INSTALL_PREFIX}/include/sparksee")  # Depends on Common, LanguageProcessor, and sparksee graph database
                                                                 # I copied the header files, i.e., sparksee/*/*.h and libsparksee.so in CMAKE_INSTALL_PREFIX.
                                                                  
## Build shared library ##
ADD_DEFINITIONS(-DLPP_BUILDING_LIB)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${MY_SOURCE_FILES})

## Install ##
INSTALL(FILES ${MY_INCLUDE_FILES} DESTINATION ${MY_INSTALL_INCLUDE_PATH})  # .h files
install(TARGETS ${PROJECT_NAME} DESTINATION ${MY_INSTALL_LIBRARY_PATH})	   # .so
install(FILES ${MY_CONF_FILES} DESTINATION ${MY_INSTALL_CONF_PATH})   # Configuration file / license


##############################################################################################
## Manager/ Test ##
## Process subdirectories here, Test binary ##
##############################################################################################
enable_testing()
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/Ontology-Manager")

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
