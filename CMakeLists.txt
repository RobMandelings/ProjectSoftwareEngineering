cmake_minimum_required(VERSION 3.10)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

include_directories(src/includes/)
include_directories(src/includes/xmlparser)

# Set include dir (gtest)
include_directories(gtest/include)

# Set Library dir (gtest)
link_directories(gtest/lib)

add_executable(ProjectSoftwareEngineering
        src/main.cpp
        src/Station.h src/Station.cpp
        src/Tram.h src/Tram.cpp
        src/library.h
        src/includes/xmlparser/tinystr.cpp src/includes/xmlparser/tinystr.h
        src/includes/xmlparser/tinyxml.h src/includes/xmlparser/tinyxml.cpp
        src/includes/xmlparser/tinyxmlerror.cpp
        src/includes/xmlparser/tinyxmlparser.cpp
        src/metroUtils.h
        src/metroUtils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/Track.cpp src/Track.h src/TrackNode.cpp src/TrackNode.h)

## Set source files for RELEASE target
#set(RELEASE_SOURCE_FILES src/TicTacToe.cpp src/TicTacToeMain.cpp)
#
## Set source files for DEBUG target
#set(DEBUG_SOURCE_FILES src/TicTacToe.cpp src/TicTacToeTests.cpp)
#
## Create RELEASE target
#add_executable(ttt ${RELEASE_SOURCE_FILES})
#
## Create DEBUG target
#add_executable(ttt_debug ${DEBUG_SOURCE_FILES})

## Link library
#target_link_libraries(ttt_debug gtest)