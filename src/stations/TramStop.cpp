//
// Created by Rob Mandelings on 2/04/2020.
//

#include "TramStop.h"

Line* TramStop::getLine() const {
    REQUIRE(this->properlyInitialized(),"TramStop must be initialized before its member variables are used.");
    return m_line;
}
