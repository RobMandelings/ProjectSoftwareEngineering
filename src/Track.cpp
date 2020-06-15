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
    ENSURE(sourcePlatform, "sourceStation may not be NULL");
    ENSURE(destinationPlatform, "destinationStation may not be NULL");
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
    REQUIRE(getStopSignal(), "This track does not have a stop signal and thus cannot have a waiting list");
    REQUIRE((int) m_waitingTrams.size() <= getStopSignal()->getMaxAmountOfTrams(), "The amount of trams in m_waitingTrams is greater than the allowed maximum");
    return m_waitingTrams;
}

void Track::addWaitingTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(tram, "The tram given may not be NULL");
    REQUIRE(m_stopSignal, "Cannot add waiting tram: this track doesn't have a stopsignal");
    REQUIRE(!tramCapacityReached(), "Cannot add waiting tram: the tram capacity is already reached");
    
    unsigned int oldSize = m_waitingTrams.size();
    
    m_waitingTrams.push_back(tram);
    
    ENSURE(m_waitingTrams.size()>oldSize, "A waiting tram must be added after addWaitingTram is called.");
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
    REQUIRE(speedSignal != NULL, "The speed signal given is NULL, can only set variable to non-NULL values");
    REQUIRE(m_speedSignal == NULL, "The speedsignal is already set!");
    m_speedSignal = speedSignal;
    ENSURE(m_speedSignal == speedSignal, "The speed signal must be properly set to its parameter.");
}

void Track::setStopSignal(StopSignal* stopSignal) {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(stopSignal != NULL, "The stop signal given is NULL, can only set variable to non-NULL values");
    REQUIRE(m_stopSignal == NULL, "The stopSignal is already set!");
    m_stopSignal = stopSignal;
    ENSURE(m_stopSignal == stopSignal, "The stop signal must be properly set to its parameter.");
}

bool Track::tramCapacityReached() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(m_stopSignal, "This track does not have a stop signal. The function tramcapacityReached() should not be called");
    REQUIRE(((int) m_waitingTrams.size() + (hasRidingTram() ? 1 : 0)) <= m_stopSignal->getMaxAmountOfTrams(), "There are more trams than this track can hold in the queue!");
    return (((int) m_waitingTrams.size() + (hasRidingTram() ? 1 : 0)) == m_stopSignal->getMaxAmountOfTrams());
}

bool Track::hasRidingTram() const {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
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