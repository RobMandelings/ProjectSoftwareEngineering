//
// Created by Rob Mandelings on 2/04/2020.
//

#include "TramStop.h"

StationType TramStop::getType() const {
    return ABOVE_GROUND;
}

Track* TramStop::getTrack() const {
    return m_track;
}