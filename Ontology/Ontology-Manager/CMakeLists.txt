#project(Test)

file(GLOB_RECURSE MY_TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE MY_TEST_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")


# Link to library and include files from installation
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${MY_INSTALL_INCLUDE_PATH} ${MY_TEST_INCLUDE_FILES})
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_INSTALL_PREFIX}/lib")

link_directories("${CMAKE_INSTALL_PREFIX}/lib")
message("${CMAKE_INSTALL_PREFIX}/lib")

add_executable(Manager ${MY_TEST_SOURCE_FILES})
target_link_libraries(Manager Ontology Common tinyxml LanguageProcessor sparksee )  # Note: The order of the lib is important

message(Manager source: ${MY_TEST_SOURCE_FILES})
message(Manager header: ${MY_TEST_INCLUDE_FILES})
