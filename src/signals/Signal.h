//
// Created by Rob Mandelings on 8/04/2020.
//

#pragma once

#include "Track.h"

class Signal {

private:

    /** The track belonging to this signal */
    Track* m_track;

    Signal* _initCheck;

public:

    /**
     * @brief simple constructor
     * @param track: the track to which the signal belongs
     *
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    explicit Signal(Track* track);

    /**
     * @brief simple getter
     * @return the track belonging to this signal
     \n REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
     */
    Track* getTrack() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};