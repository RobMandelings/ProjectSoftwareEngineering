//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "lines/Line.h"

Track* MetroStation::getTrack(int index) const {
    REQUIRE(index >= 0, "Metrostation getTrack(): index given is invalid");
    return m_tracks.at(index);
}

void MetroStation::addTrack(std::pair<int, Track*> track) {
    REQUIRE(track.first >= 0, "Metrostation addTrack(): the index of the track to insert is invalid (neg.)");
    REQUIRE(track.second != NULL, "The track pointer cannot be NULL");
    REQUIRE(m_tracks.at(track.first) == NULL, "There already exists a track at this index");
    m_tracks.insert(track);
}