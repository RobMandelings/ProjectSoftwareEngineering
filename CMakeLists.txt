cmake_minimum_required(VERSION 3.10)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

include_directories(src/libs)
include_directories(src/libs/xmlparser)
include_directories(src/tests)
include_directories(gtest/include/gtest)
include_directories(src/utils)

# Set include dir (gtest)
include_directories(gtest/include)

# Set Library dir (gtest)
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/main.cpp
        src/Station.h src/Station.cpp
        src/Tram.h src/Tram.cpp
        src/library.h
        src/libs/xmlparser/tinystr.cpp src/libs/xmlparser/tinystr.h
        src/libs/xmlparser/tinyxml.h src/libs/xmlparser/tinyxml.cpp
        src/libs/xmlparser/tinyxmlerror.cpp
        src/libs/xmlparser/tinyxmlparser.cpp
        src/utils/metro_utils.h
        src/utils/metro_utils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/Track.cpp src/Track.h src/TrackNode.cpp src/TrackNode.h src/utils/metro_parser.cpp src/utils/metro_parser.h src/utils/simulation_utils.cpp src/utils/simulation_utils.h
        )

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/Station.h src/Station.cpp
        src/Tram.h src/Tram.cpp
        src/library.h
        src/libs/xmlparser/tinystr.cpp src/libs/xmlparser/tinystr.h
        src/libs/xmlparser/tinyxml.h src/libs/xmlparser/tinyxml.cpp
        src/libs/xmlparser/tinyxmlerror.cpp
        src/libs/xmlparser/tinyxmlparser.cpp
        src/utils/metro_utils.h
        src/utils/metro_utils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/Track.cpp src/Track.h src/TrackNode.cpp src/TrackNode.h src/utils/metro_parser.cpp src/utils/metro_parser.h src/utils/simulation_utils.cpp src/utils/simulation_utils.h
        src/tests/outputTest.cpp src/tests/inputTest.cpp)

# Create RELEASE target
add_executable(metroNet ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(metroNet_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(metroNet_debug gtest)