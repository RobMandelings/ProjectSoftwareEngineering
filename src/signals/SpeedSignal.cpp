//
// Created by Rob Mandelings on 16/04/2020.
//

#include "SpeedSignal.h"

SpeedSignal::~SpeedSignal() {}


SpeedSignal::SpeedSignal(Track* track, double m_speed) :
        Signal(track),
        m_speed(m_speed) {
}

double SpeedSignal::getSpeed() const {
    return m_speed;
}