//
// Created by Rob Mandelings on 7/04/2020.
//

#include "Track.h"
#include "library.h"
#include "constants.h"
#include "StopSignal.h"
#include "SpeedSignal.h"
#include "Platform.h"

Track::Track(Platform* sourcePlatform, Platform* destinationPlatform) :
        m_speedSignal(NULL),
        m_stopSignal(NULL),
        m_sourcePlatform(sourcePlatform),
        m_destinationPlatform(destinationPlatform),
        m_ridingTram(NULL) {
    Track::_initCheck = this;
    ENSURE(sourcePlatform, "sourceStation may not be null!");
    ENSURE(destinationPlatform, "destinationStation may not be null!");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Platform* Track::getSourcePlatform() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(m_sourcePlatform, "sourceStation cannot be null!");
    return m_sourcePlatform;
}

Platform* Track::getDestinationPlatform() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(m_destinationPlatform, "destinationStation cannot be null!");
    return m_destinationPlatform;
}

std::deque<Tram*>& Track::getWaitingTrams() {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    return m_waitingTrams;
}

Tram* Track::getFirstTramInLine() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    return m_waitingTrams.front();
}

void Track::addWaitingTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(tram, "the tram to be added to track should not be null!");
    m_waitingTrams.push_back(tram);
}

SpeedSignal* Track::getSpeedSignal() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    return m_speedSignal;
}

StopSignal* Track::getStopSignal() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    return m_stopSignal;
}

void Track::setSpeedSignal(SpeedSignal* speedSignal) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    m_speedSignal = speedSignal;
}

void Track::setStopSignal(StopSignal* stopSignal) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    m_stopSignal = stopSignal;
}

bool Track::tramCapacityReached() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(m_stopSignal, "This track does not have a stop signal. The function hasSpace() should not be called");
    REQUIRE(((int) m_waitingTrams.size() + (hasRidingTram() ? 1 : 0)) <= m_stopSignal->getMaxAmountOfTrams(), "There are more trams than this track can hold in the queue!");

    return (((int) m_waitingTrams.size() + (hasRidingTram() ? 1 : 0)) == m_stopSignal->getMaxAmountOfTrams());
}

bool Track::hasRidingTram() const {
    return m_ridingTram;
}

void Track::setRidingTram(Tram* ridingTram) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(!m_ridingTram, "A tram is already riding on this track!");
    REQUIRE(!m_stopSignal || !tramCapacityReached(), "The tram capacity on this track is already reached! Cannot set the riding tram");
    m_ridingTram = ridingTram;
}

void Track::removeTram() {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    m_ridingTram = NULL;
}

bool Track::properlyInitialized() const {
    return (Track::_initCheck == this);
}

std::ostream& operator<<(ostream& os, Track& track) {
    return os << "track: 'source: " << track.getSourcePlatform() << ", destination: " << track.getDestinationPlatform() << "'";
}

std::ostream& operator<<(ostream& os, Track* track) {
    return os << *track;
}