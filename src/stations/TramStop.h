//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Track;

class Line;
class Platform;

class TramStop : public Station {

private:

    /** The platform which is used for trams going in the 'Heen' or 'TO' Direction */
    Platform* m_platformHeen;

    /** The platform which is used for trams going in the 'Terug' or 'FROM' Direction */
    Platform* m_platformTerug;

public:

    /**
     * @brief simple constructor
     * @param platform: the platform this tramstop holds (platformheen and platformterug have the same platformnumber)
     */
    explicit TramStop(Platform* platform);

    /**
     * @brief simple getter
     * @return the to platform of this tramstop
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     */
    Platform* getPlatformTo() const;

    /**
     * @brief simple getter
     * @return the from platform of this tramstop
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     */
    Platform* getPlatformFrom() const;

    /**
     * @return the type of the platform (Above ground for a metrostation)
     */
    StationType getType() const { return ABOVE_GROUND; };

};