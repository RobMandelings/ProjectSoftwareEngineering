cmake_minimum_required(VERSION 3.15)
project(ProjectSoftwareEngineering)

set(CMAKE_CXX_STANDARD 98)

add_executable(ProjectSoftwareEngineering src/main.cpp src/Station.cpp src/Station.h src/library.h src/Tram.cpp src/Tram.h)
include_directories(src/includes/)
include_directories(src/includes/xmlparser)