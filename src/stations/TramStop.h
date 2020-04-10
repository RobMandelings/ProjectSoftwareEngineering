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

    Platform* m_platform;

public:

    explicit TramStop(Platform* platform);

    Platform* getPlatform() const;

    StationType getType() const { return ABOVE_GROUND; };

};