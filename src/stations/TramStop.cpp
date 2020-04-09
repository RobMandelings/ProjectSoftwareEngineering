//
// Created by Rob Mandelings on 2/04/2020.
//

#include "TramStop.h"

Track* TramStop::getTrack() const {
    return m_outgoingTrack;
}

void TramStop::setTram(Tram* tram) {
    REQUIRE(!hasTram(), " cannot set tram: there already is a tram in the station!");
    m_tram = tram;
}

Tram* TramStop::getTram() const {
    return m_tram;
}

bool TramStop::hasTram() const {
    return getTram() != NULL;
}