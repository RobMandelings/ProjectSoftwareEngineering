//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;

class TramStop : public virtual Station {

private:

    Track* m_track;

public:

    StationType getType() const {return ABOVE_GROUND; };

    Track* getTrack() const;

};