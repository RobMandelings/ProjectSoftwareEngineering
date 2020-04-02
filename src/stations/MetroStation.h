//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;

class MetroStation : public virtual Station {

private:

    std::vector<Track*> m_tracks;

public:

    StationType getType() const {return UNDERGROUND; };

    std::vector<Track*> getTracks() const;

    Track* getTrack(int index) const;

    void addTrack(Track* track);

};