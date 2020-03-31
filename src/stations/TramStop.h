//
// Created by Rob Mandelings on 31/03/2020.
//

#pragma once

#include "Station.h"

class TramStop : public virtual Station {

    virtual const char* getType() const;

};


