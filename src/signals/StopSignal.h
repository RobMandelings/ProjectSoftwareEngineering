//
// Created by Rob Mandelings on 16/04/2020.
//

#pragma once

#include "Signal.h"

class StopSignal : public Signal {

private:

    /** The max amount (buffer) of trams that can be put on the track */
    int m_maxAmountOfTrams;

public:

    /**
     * @brief simple destructor
     */
    virtual ~StopSignal();

    /**
     * @brief simple constructor
     * @param track: the track corresponding to this signal
     * @param m_maxAmountOfTrams: the max amount of trams the track should be able to hold
     \n ENSURE(this->properlyInitialized(), "Constructor must end...");
     \n ENSURE(track != NULL, "Track given is NULL");
     \n ENSURE(m_maxAmountOfTrams > 0, "The buffer for the stop signal should be greater than 0!");
     */
    StopSignal(Track* track, int m_maxAmountOfTrams);

    /**
     * @brief simple getter
     * @return the max amount of trams the track can hold
     \n REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
     */
    int getMaxAmountOfTrams() const;

};