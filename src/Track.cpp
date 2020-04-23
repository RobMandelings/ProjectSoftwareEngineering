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
        m_amountOfTrams(0) {
    Track::_initCheck = this;
    ENSURE(sourcePlatform, "sourceStation may not be null!");
    ENSURE(destinationPlatform, "destinationStation may not be null!");
    ENSURE(m_amountOfTrams == 0, "Amount of trams has to be set.");
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

void Track::increaseAmountOfTrams() {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    m_amountOfTrams++;
    ENSURE(m_amountOfTrams <= constants::MAX_TRAMS_ON_TRACK, "The maximum amount of trams has been reached.");
}

void Track::deleteTram() {
    REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    REQUIRE(m_amountOfTrams > 0, "The amount of trams is not greater than 0 but deleteTram is still called.");
    m_amountOfTrams--;
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
    REQUIRE(m_amountOfTrams <= m_stopSignal->getMaxAmountOfTrams(), "There are more trams than this track can hold in the queue!");
    return (m_amountOfTrams == m_stopSignal->getMaxAmountOfTrams());
}

int Track::getAmountOfTrams() const{
    return this->m_amountOfTrams;
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