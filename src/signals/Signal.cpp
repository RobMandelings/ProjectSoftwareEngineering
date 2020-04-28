//
// Created by Rob Mandelings on 8/04/2020.
//

#include "library.h"
#include "Signal.h"

Signal::Signal(Track* track) :
        m_track(track) {
    _initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Track* Signal::getTrack() const {
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
    return m_track;
}

bool Signal::properlyInitialized() const {
    return Signal::_initCheck == this;
}

#include "SpeedSignal.h"

SpeedSignal::~SpeedSignal() {}


SpeedSignal::SpeedSignal(Track* track, double m_speed) :
        Signal(track),
        m_speed(m_speed) {
}

double SpeedSignal::getSpeed() const {
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
    return m_speed;
}

#include "StopSignal.h"

StopSignal::~StopSignal() {}

StopSignal::StopSignal(Track* track, int m_maxAmountOfTrams) :
        Signal(track),
        m_maxAmountOfTrams(m_maxAmountOfTrams) {
}

int StopSignal::getMaxAmountOfTrams() const {
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
    return m_maxAmountOfTrams;
}