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
     */
    StopSignal(Track* track, int m_maxAmountOfTrams);

    /**
     * @brief simple getter
     * @return the max amount of trams the track can hold
     */
    int getMaxAmountOfTrams() const;

};