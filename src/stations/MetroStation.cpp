//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "Line.h"
#include "Track.h"

std::vector<Platform*> MetroStation::getPlatforms() const {
    return m_platforms;
};

void MetroStation::addPlatform(Platform* platform) {
    m_platforms.push_back(platform);
}
