cmake_minimum_required(VERSION 3.10)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

include_directories(src/includes/)
include_directories(src/includes/xmlparser)
include_directories(gtest/include)
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
        src/includes/xmlparser/tinystr.cpp src/includes/xmlparser/tinystr.h
        src/includes/xmlparser/tinyxml.h src/includes/xmlparser/tinyxml.cpp
        src/includes/xmlparser/tinyxmlerror.cpp
        src/includes/xmlparser/tinyxmlparser.cpp
        src/utils/metroUtils.h
        src/utils/metroUtils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/Track.cpp src/Track.h src/TrackNode.cpp src/TrackNode.h src/utils/metroParser.cpp src/utils/metroParser.h
        )

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/Station.h src/Station.cpp
        src/Tram.h src/Tram.cpp
        src/library.h
        src/includes/xmlparser/tinystr.cpp src/includes/xmlparser/tinystr.h
        src/includes/xmlparser/tinyxml.h src/includes/xmlparser/tinyxml.cpp
        src/includes/xmlparser/tinyxmlerror.cpp
        src/includes/xmlparser/tinyxmlparser.cpp
        src/utils/metroUtils.h
        src/utils/metroUtils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/Track.cpp src/Track.h src/TrackNode.cpp src/TrackNode.h src/utils/metroParser.cpp src/utils/metroParser.h
        src/tests/outputTest.cpp)

# Create RELEASE target
add_executable(metroNet ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(metroNet_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(metroNet_debug gtest)