cmake_minimum_required(VERSION 3.10)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

include_directories(src/)
include_directories(src/libs)
include_directories(src/libs/xmlparser)
include_directories(src/tests)
include_directories(gtest/include/gtest)
include_directories(src/utils)
include_directories(src/trams)
include_directories(src/lines/)
include_directories(src/stations)
include_directories(src/time)
include_directories(src/platform)
include_directories(src/signals)

# Set include dir (gtest)
include_directories(gtest/include)

# Set Library dir (gtest)
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/main.cpp
        src/stations/Station.h src/stations/Station.cpp
        src/trams/Tram.h src/trams/Tram.cpp
        src/library.h
        src/libs/xmlparser/tinystr.cpp src/libs/xmlparser/tinystr.h
        src/libs/xmlparser/tinyxml.h src/libs/xmlparser/tinyxml.cpp
        src/libs/xmlparser/tinyxmlerror.cpp
        src/libs/xmlparser/tinyxmlparser.cpp
        src/utils/metro_utils.h
        src/utils/metro_utils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/lines/Line.cpp src/lines/Line.h src/lines/LineNode.cpp src/lines/LineNode.h src/utils/metro_parser.cpp src/utils/metro_parser.h
        src/utils/simulation_utils.cpp src/utils/simulation_utils.h
        src/trams/Albatros.cpp
        src/trams/Albatros.h src/trams/PCC.cpp src/trams/PCC.h
        src/Track.cpp src/Track.h
        src/time/Timer.cpp
        src/time/Timer.h
        src/utils/constants.cpp
        src/utils/constants.h
        src/signals/Signal.cpp
        src/signals/Signal.h
        src/stations/Platform.h
        src/stations/Platform.cpp
        src/utils/Direction.cpp
        src/utils/Direction.h
        src/signals/SpeedSignal.cpp
        src/signals/SpeedSignal.h
        src/signals/StopSignal.cpp
        src/signals/StopSignal.h
        src/time/SimulationTime.cpp
        src/time/SimulationTime.h
        src/utils/FileHandler.cpp
        src/utils/FileHandler.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/stations/Station.h src/stations/Station.cpp
        src/stations/MetroStation.cpp
        src/stations/MetroStation.h
        src/trams/Tram.h src/trams/Tram.cpp
        src/library.h
        src/libs/xmlparser/tinystr.cpp src/libs/xmlparser/tinystr.h
        src/libs/xmlparser/tinyxml.h src/libs/xmlparser/tinyxml.cpp
        src/libs/xmlparser/tinyxmlerror.cpp
        src/libs/xmlparser/tinyxmlparser.cpp
        src/utils/metro_utils.h
        src/utils/metro_utils.cpp
        src/MetroNet.h
        src/MetroNet.cpp
        src/lines/Line.cpp src/lines/Line.h src/lines/LineNode.cpp src/lines/LineNode.h src/utils/metro_parser.cpp src/utils/metro_parser.h
        src/utils/simulation_utils.cpp src/utils/simulation_utils.h
        src/tests/outputTest.cpp src/tests/inputTest.cpp src/tests/DesignByContract.h
        src/trams/Albatros.cpp src/trams/Albatros.h src/trams/PCC.h src/trams/PCC.cpp
        src/stations/TramStop.cpp src/stations/TramStop.h src/Track.cpp src/Track.h
        src/time/Timer.cpp src/time/Timer.h src/utils/constants.cpp src/utils/constants.h src/signals/Signal.cpp src/signals/Signal.h
        src/stations/Platform.h src/stations/Platform.cpp
        src/time/SimulationTime.cpp src/time/SimulationTime.h
        src/utils/FileHandler.cpp src/utils/FileHandler.h)

# Create RELEASE target
add_executable(metroNet ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(metroNet_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(metroNet_debug gtest)