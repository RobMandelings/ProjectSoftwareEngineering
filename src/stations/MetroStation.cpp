//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"

StationType MetroStation::getType() const {
    return UNDERGROUND;
}

std::vector<Track*> MetroStation::getTracks() const {
    return m_tracks;
}

Track* MetroStation::getTrack(int index) const {
    //TODO REQUIRE index < m_tracks.length
    return m_tracks.at(index);
}

void MetroStation::addTrack(Track* track) {
    Station::addTrack(track);
}
