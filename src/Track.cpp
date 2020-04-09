//
// Created by Rob Mandelings on 7/04/2020.
//

#include "Track.h"
#include "library.h"

Track::Track(Station* sourceStation, Station* destinationStation) :
        m_sourceStation(sourceStation),
        m_destinationStation(destinationStation) {
    ENSURE(sourceStation, "sourceStation may not be null!");
    ENSURE(destinationStation, "destinationStation may not be null!");
}

Station* Track::getSourceStation() const {
    REQUIRE(m_sourceStation, "sourceStation cannot be null!");
    return m_sourceStation;
}

Station* Track::getDestinationStation() const {
    REQUIRE(m_destinationStation, "destinationStation cannot be null!");
    return m_destinationStation;
}

std::queue<Tram*> Track::getWaitingTrams() const {
    return m_waitingTrams;
}

Tram* Track::getFirstTramInLine() const {
    return m_waitingTrams.front();
}

void Track::addWaitingTram(Tram* tram) {
    REQUIRE(tram, "the tram to be added to track should not be null!");
    m_waitingTrams.push(tram);
}