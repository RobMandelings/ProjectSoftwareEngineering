//
// Created by Rob Mandelings on 16/04/2020.
//

#pragma once

#include "Signal.h"

class SpeedSignal : public Signal {

private:

    /** The speed each tram will be set to if the signal is activated */
    double m_speed;

public:

    /**
     * @brief simple destructor
     */
    virtual ~SpeedSignal();

    /**
     * @brief simple constructor
     * @param track
     * @param m_speed
     *
    ENSURE(this->properlyInitialized(), "Constructor must end...");
    ENSURE(track != NULL, "Track given is NULL");
    ENSURE(m_speed > 0, "The speed for the speed signal should be greater than 0!");
     */
    SpeedSignal(Track* track, double m_speed);

    /**
     * @brief simple getter
     * @return the restricted speed at this signal
     *
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
     */
    double getSpeed() const;

};
