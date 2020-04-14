//
// Created by Rob Mandelings on 7/04/2020.
//

#include "Track.h"
#include "library.h"
#include "constants.h"

Track::Track(Platform* sourcePlatform, Platform* destinationPlatform) :
        m_sourcePlatform(sourcePlatform),
        m_destinationPlatform(destinationPlatform),
        m_amountOfTrams(0){
    ENSURE(sourcePlatform, "sourceStation may not be null!");
    ENSURE(destinationPlatform, "destinationStation may not be null!");
    ENSURE(m_amountOfTrams == 0, "Amount of trams has to be set.");
}

Platform* Track::getSourcePlatform() const {
    REQUIRE(m_sourcePlatform, "sourceStation cannot be null!");
    return m_sourcePlatform;
}

Platform* Track::getDestinationPlatform() const {
    REQUIRE(m_destinationPlatform, "destinationStation cannot be null!");
    return m_destinationPlatform;
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

void Track::addTram() {
    m_amountOfTrams++;
    ENSURE(m_amountOfTrams <= constants::MAX_TRAMS_ON_TRACK, "The maximum amount of trams has been reached.");
}

void Track::deleteTram() {
    m_amountOfTrams--;
}

bool Track::hasSpace() const {
    return (m_amountOfTrams < constants::MAX_TRAMS_ON_TRACK);
}
