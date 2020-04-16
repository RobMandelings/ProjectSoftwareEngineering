//
// Created by Rob Mandelings on 16/04/2020.
//

#pragma once

#include "Signal.h"

class SpeedSignal : public Signal {

private:

    double m_speed;

public:

    virtual ~SpeedSignal();

    SpeedSignal(Track* track, double m_speed);

    double getSpeed() const;

};
