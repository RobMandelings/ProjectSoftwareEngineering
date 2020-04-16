//
// Created by Rob Mandelings on 8/04/2020.
//

#include "Signal.h"

Signal::Signal(Track* track) :
        m_track(track) {}

Track* Signal::getTrack() const {
    return m_track;
}

#include "SpeedSignal.h"

SpeedSignal::~SpeedSignal() {}


SpeedSignal::SpeedSignal(Track* track, double m_speed) :
        Signal(track),
        m_speed(m_speed) {
}

double SpeedSignal::getSpeed() const {
    return m_speed;
}

#include "StopSignal.h"

StopSignal::~StopSignal() {}

StopSignal::StopSignal(Track* track, int m_maxAmountOfTrams) :
        Signal(track),
        m_maxAmountOfTrams(m_maxAmountOfTrams) {
}

int StopSignal::getMaxAmountOfTrams() const {
    return m_maxAmountOfTrams;
}