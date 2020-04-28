//
// Created by Rob Mandelings on 8/04/2020.
//

#pragma once

#include "Track.h"

class Signal {

private:

    Track* m_track;

    Signal* _initCheck;

public:

    explicit Signal(Track* track);

    /**
     * @brief simple getter
     * @return the track belonging to this signal
     */
    Track* getTrack() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};