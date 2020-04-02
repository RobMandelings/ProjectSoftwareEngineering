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

    /**
    \n REQUIRE(this->properlyInitialized(),"TramStop must be initialized before its member variables are used.");
    */
    Line* getLine() const;

};