//
// Created by Rob Mandelings on 8/04/2020.
//

#include "Signal.h"

Signal::Signal(Track* track) :
        m_track(track) {}

Track* Signal::getTrack() const {
    return m_track;
}