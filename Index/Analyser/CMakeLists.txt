#project(Test)

file(GLOB_RECURSE MY_TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE MY_TEST_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")


# Link to library and include files from installation
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${MY_TEST_INCLUDE_FILES}
                                            "${CMAKE_INSTALL_PREFIX}/include/Index"
                                            "${CMAKE_INSTALL_PREFIX}/include/LanguageProcessor"
                                            "${CMAKE_INSTALL_PREFIX}/include/Common"
                                                                )
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_INSTALL_PREFIX}/lib")

link_directories("${CMAKE_INSTALL_PREFIX}/lib")

add_executable(Test ${MY_TEST_SOURCE_FILES})
target_link_libraries(Test Index LanguageProcessor Common tinyxml)

message("==== Test ====")
message("Source: ${MY_TEST_SOURCE_FILES}")
message("Header: ${MY_TEST_INCLUDE_FILES}")
message("Link library: ${CMAKE_LIBRARY_PATH}")
message("Include: ${CMAKE_INCLUDE_PATH}")
