//
// Created by Rob Mandelings on 7/04/2020.
//

#pragma once

#include <string>

namespace constants {

    /**
     * How many updates per second you want the program to run at
     */
    extern const int UPDATES_PER_SECOND;

    /**
     * The time in seconds a tram should wait at a station before leaving again
     */
    extern const double TRAM_WAIT_TIME;

    /**
     * The time the program should run
     */
    extern const double RUNTIME_SECONDS;

    /**
     * Which file the events during runtime will be written to
     */
    extern const char* EVENTS_OUTPUT_FILE;

    /**
     * The specified hour when the simulation should start
     */
    extern const int SIMULATION_START_HOUR;

    /**
     * The specified minute when the simulation should start
     */
    extern const int SIMULATION_START_MINUTE;

    /**
     * The specified second when the simulation should start
     */
    extern const int SIMULATION_START_SECOND;

}