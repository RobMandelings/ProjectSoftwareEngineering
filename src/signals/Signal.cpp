//
// Created by Rob Mandelings on 8/04/2020.
//

#include "library.h"
#include "Signal.h"

#include "SpeedSignal.h"
#include "StopSignal.h"

/** Signal (abstract parent class) */

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

/** Speed signal */

SpeedSignal::~SpeedSignal() {}


SpeedSignal::SpeedSignal(Track* track, double m_speed) :
        Signal(track),
        m_speed(m_speed) {
    ENSURE(this->properlyInitialized(), "Constructor must end...");
    ENSURE(track != NULL, "Track given is NULL");
    ENSURE(m_speed > 0, "The speed for the speed signal should be greater than 0!");
}

double SpeedSignal::getSpeed() const {
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
    return m_speed;
}

/** Stop signal */

StopSignal::~StopSignal() {}

StopSignal::StopSignal(Track* track, int m_maxAmountOfTrams) :
        Signal(track),
        m_maxAmountOfTrams(m_maxAmountOfTrams) {
    ENSURE(this->properlyInitialized(), "Constructor must end...");
    ENSURE(track != NULL, "Track given is NULL");
    ENSURE(m_maxAmountOfTrams > 0, "The buffer for the stop signal should be greater than 0!");
}

int StopSignal::getMaxAmountOfTrams() const {
    REQUIRE(this->properlyInitialized(),"Signal must be properly initialized to use its member variables.");
    return m_maxAmountOfTrams;
}