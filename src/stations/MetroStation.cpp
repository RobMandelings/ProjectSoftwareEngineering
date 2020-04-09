//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "lines/Line.h"
#include "Track.h"

Track* MetroStation::getTrack(int trackNumber) const {
    REQUIRE(trackNumber >= 0, "Metrostation getTrack(): index given is invalid");
    return m_tracks.at(trackNumber);
}

Track* MetroStation::getTrackForDestination(Station* destinationStation) {

    REQUIRE(destinationStation != NULL, "The destionation station given is NULL");

    Track* trackForDestination = NULL;
    for (std::map<int, Track*>::iterator trackIt = m_tracks.begin(); trackIt != m_tracks.end(); trackIt++) {
        if (trackIt->second->getDestinationStation() == destinationStation) {
            trackForDestination = trackIt->second;
        }
    }

    ASSERT(trackForDestination != NULL, "The track for the given destination wasn't found.");
    return trackForDestination;
}

void MetroStation::addTrack(std::pair<int, Track*> track) {
    REQUIRE(track.first >= 0, "Metrostation addTrack(): the index of the track to insert is invalid (neg.)");
    REQUIRE(track.second != NULL, "The track pointer cannot be NULL");
    REQUIRE(m_tracks.at(track.first) == NULL, "There already exists a track at this index");
    m_tracks.insert(track);
}
