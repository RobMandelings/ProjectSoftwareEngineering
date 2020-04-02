//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Line;

class TramStop : public virtual Station {

private:

    Line* m_line;

public:

    StationType getType() const {return ABOVE_GROUND; };

    Line* getLine() const;

};