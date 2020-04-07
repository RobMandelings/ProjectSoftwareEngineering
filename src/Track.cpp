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

std::vector<Tram*> Track::getCurrentTrams() const {
    return m_currentTrams;
}

void Track::addTram(Tram* tram) {
    REQUIRE(tram, "the tram to be added to track should not be null!");
    m_currentTrams.push_back(tram);
}