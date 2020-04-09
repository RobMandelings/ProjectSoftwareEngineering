//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"
#include "library.h"
#include "map"

class Track;

class Line;

class MetroStation : public virtual Station {

private:

    std::map<int, Track*> m_outgoingTracks;

    std::map<int, Tram*> m_trams;

public:

    void setTramOn(int trackNumber, Tram* tram);

    Tram* getTramOn(int trackNumber) const;

    bool hasTramOn(int trackNumber) const;

    StationType getType() const { return UNDERGROUND; };

    /**
     \n REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
     \n REQUIRE(line!=NULL && line->properlyInitialized(),"Line cannot be NULL.");
     */
    Track* getTrack(int trackNumber) const;

    Track* getTrackForDestination(Station* destinationStation);

    void addTrack(std::pair<int, Track*> track);

};