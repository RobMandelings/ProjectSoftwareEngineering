//
// Created by Rob Mandelings on 16/04/2020.
//

#include "StopSignal.h"

StopSignal::~StopSignal() {}

StopSignal::StopSignal(Track* track, int m_maxAmountOfTrams) :
        Signal(track),
        m_maxAmountOfTrams(m_maxAmountOfTrams) {
}

int StopSignal::getMaxAmountOfTrams() const {
    return m_maxAmountOfTrams;
}