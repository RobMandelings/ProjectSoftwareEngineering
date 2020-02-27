cmake_minimum_required(VERSION 3.15)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)

include_directories(src/includes/)
include_directories(src/includes/xmlparser)
add_executable(ProjectSoftwareEngineering
        src/main.cpp
        src/Station.h src/Station.cpp
        src/Tram.h src/Tram.cpp
        src/library.h
        src/includes/xmlparser/tinystr.cpp src/includes/xmlparser/tinystr.h
        src/includes/xmlparser/tinyxml.h src/includes/xmlparser/tinyxml.cpp
        src/includes/xmlparser/tinyxmlerror.cpp
        src/includes/xmlparser/tinyxmlparser.cpp
        )