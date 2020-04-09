//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;

class Line;

class TramStop : public virtual Station {

private:

    Track* m_outgoingTrack;
    Tram* m_tram;

public:

    void setTram(Tram* tram);

    Tram* getTram() const;

    bool hasTram() const;

    StationType getType() const { return ABOVE_GROUND; };

    Track* getTrack() const;

};