project(plumber)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
