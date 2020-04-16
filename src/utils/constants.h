//
// Created by Rob Mandelings on 7/04/2020.
//

#pragma once

namespace constants {

    /**
     * How many updates per second you want the program to run at
     */
    extern const int UPDATES_PER_SECOND;

    /**
     * The time in seconds a tram should wait at a station before leaving again
     */
    extern const double TRAM_WAIT_TIME;

    extern const double TRAM_ACCELERATION;

    /**
     * The length of each track between stations in km
     */
    extern const double TRACK_LENGTH;

    /**
     * The time the program should run
     */
    extern const double RUNTIME_SECONDS;

    /**
     *
     */
    extern const int MAX_TRAMS_ON_TRACK;

    // TODO add start time of simulation (12:00:00)

}