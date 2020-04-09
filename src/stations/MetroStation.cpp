//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "Line.h"
#include "Track.h"
#include "Platform.h"

std::vector<Platform*> MetroStation::getPlatforms() const {
    return m_platforms;
}