//
// Created by Rob Mandelings on 16/04/2020.
//

#pragma once

#include "Signal.h"

class StopSignal : public Signal {

private:

    int m_maxAmountOfTrams;

public:

    ~StopSignal();

    StopSignal(Track* track, int m_maxAmountOfTrams);

    int getMaxAmountOfTrams() const;

};