//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;

class Line;
class Platform;

class TramStop : public Station {

private:

    Platform* m_platformHeen;
    Platform* m_platformTerug;

public:

    explicit TramStop(Platform* platform);

    Platform* getPlatformHeen() const;

    Platform* getPlatformTerug() const;

    Platform* getPlatform(int platformNumber);

    StationType getType() const { return ABOVE_GROUND; };

};