##############################################################################################
## CMakeList ##
## LanguageProcessor    ##
##############################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)
PROJECT(LanguageProcessor)

#
# Set:
# Compiler flags
# Build & Install directories
#

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
#SET(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
#SET(CMAKE_INSTALL_PREFIX "/home/search-engine/install")

##############################################################################################
## Sources path (cpp/h)
## Install path
## List of Source: cpp, h, conf files to be built ##
##############################################################################################
FILE(GLOB_RECURSE MY_SOURCE_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/Tokeniser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Porter2Stemmer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Dict.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/info_helper.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/load_wordnet.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Wordnet.cpp")

FILE(GLOB_RECURSE MY_INCLUDE_FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/Tokeniser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Porter2Stemmer.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Dict.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/info_helper.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/load_wordnet.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/pos_t.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Wordnet.h")

FILE(GLOB_RECURSE MY_DICT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Dictionary/*")

#
# Target/Install path
#

set(MY_INSTALL_LIBRARY_PATH  "${CMAKE_INSTALL_PREFIX}/lib")
set(MY_INSTALL_INCLUDE_PATH  "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")
set(MY_INSTALL_DICT_PATH "${CMAKE_INSTALL_PREFIX}/dict/")

##############################################################################################
## #define
## Define variables, used in C++ as #define ..
##############################################################################################
add_definitions(-DDIR_WN_DIC="${MY_INSTALL_DICT_PATH}")
add_definitions(-DENGLISH_WORDS="${MY_INSTALL_DICT_PATH}/small-dict.txt")


##############################################################################################
## Boost
##############################################################################################
option(ENABLE_CYCLIC_CHECK "Enable cyclic checking" OFF)
option(LANGUAGEPROCESSOR_USE_STATIC_BOOST_LIBS "Use static boost libraries" OFF)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS
  filesystem
  regex
  system
  thread
  graph
  REQUIRED
)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ${LANGUAGEPROCESSOR_USE_STATIC_BOOST_LIBS})

set(LanguageProcessor_boost_libs
  ${Boost_LIBRARIES}
  ${Boost_FILESYSTEM_LIBRARIES}
  ${Boost_REGEX_LIBRARIES}
  ${Boost_SYSTEM_LIBRARIES}
  ${Boost_THREAD_LIBRARIES}
  ${Boost_GRAPH_LIBRARIES}
)

##############################################################################################
## Build
## Include my header files, required to build the cpp files
## The Wordnet files are dependent on common so as common files on Wordnet, 
## they can find even if included locally using ""
## shared build, therefore, my header files only required
##############################################################################################
INCLUDE_DIRECTORIES(${MY_INCLUDE_FILES}
                    "${CMAKE_INSTALL_PREFIX}/include/Common")

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
#message(" Version:        ${Commom_VERSION}")
message(" Install Prefix:${CMAKE_INSTALL_PREFIX}")
message(" Build Type:     ${CMAKE_BUILD_TYPE}")
message(" Architecture|System :   ${CMAKE_SYSTEM_PROCESSOR} | ${CMAKE_SYSTEM_NAME}")
message(" Boost Include|Library:  ${Boost_INCLUDE_DIRS} | ${Boost_LIBRARY_DIRS}")
message(" SourcePath Source|Include|Dict: ${MY_SOURCE_FILES} | ${MY_INCLUDE_FILES} | ${MY_DICT_FILES}")
message(" Install Include|Library|Dict:   ${MY_INSTALL_INCLUDE_PATH} | ${MY_INSTALL_LIBRARY_PATH} | ${MY_INSTALL_DICT_PATH}")
