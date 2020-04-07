//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;
class Line;

class TramStop : public virtual Station {

private:

    std::pair<int, Track*> m_track;

public:


    StationType getType() const {return ABOVE_GROUND; };

    std::pair<int, Track*> getTrack() const;

};