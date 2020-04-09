//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"
#include "library.h"
#include "map"

class Track;

class Line;

class Platform;

class MetroStation : public virtual Station {

private:

    std::vector<Platform*> m_platforms;

public:

    std::vector<Platform*> getPlatforms() const;

    void addPlatform(Platform* platform);

    StationType getType() const { return UNDERGROUND; };

};