//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "lines/Line.h"
#include "Track.h"

void MetroStation::setTramOn(int trackNumber, Tram* tram) {
    REQUIRE(!hasTramOn(trackNumber), " cannot set tram: there already is a tram in the station!");
    m_trams.insert(std::make_pair(trackNumber, tram));
}

Tram* MetroStation::getTramOn(int trackNumber) const {
    return m_trams.at(trackNumber);
}

bool MetroStation::hasTramOn(int trackNumber) const {
    return getTramOn(trackNumber) != NULL;
}

Track* MetroStation::getTrack(int trackNumber) const {
    REQUIRE(trackNumber >= 0, "Metrostation getTrack(): index given is invalid");
    return m_outgoingTracks.at(trackNumber);
}

Track* MetroStation::getTrackForDestination(Station* destinationStation) {

    REQUIRE(destinationStation != NULL, "The destionation station given is NULL");

    Track* trackForDestination = NULL;
    for (std::map<int, Track*>::iterator trackIt = m_outgoingTracks.begin(); trackIt != m_outgoingTracks.end(); trackIt++) {
        if (trackIt->second->getDestinationStation() == destinationStation) {
            trackForDestination = trackIt->second;
        }
    }

    ENSURE(trackForDestination != NULL, "The track for the given destination wasn't found.");
    return trackForDestination;
}

void MetroStation::addTrack(std::pair<int, Track*> track) {
    REQUIRE(track.first >= 0, "Metrostation addTrack(): the index of the track to insert is invalid (neg.)");
    REQUIRE(track.second != NULL, "The track pointer cannot be NULL");
    REQUIRE(m_outgoingTracks.at(track.first) == NULL, "There already exists a track at this index");
    m_outgoingTracks.insert(track);
}
