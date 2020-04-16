//
// Created by Rob Mandelings on 8/04/2020.
//

#pragma once

#include "Track.h"

class Signal {

private:

    Track* m_track;

public:

    virtual ~Signal() = 0;

    explicit Signal(Track* track);

    Track* getTrack() const;

};