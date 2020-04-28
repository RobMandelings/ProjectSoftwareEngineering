//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"
#include "library.h"
#include "map"

class Track;

class Line;

class Platform;

class MetroStation : public Station {

private:

    /** The platforms this metrostation holds */
    std::vector<Platform*> m_platforms;

public:

    /**
     * @brief simple getter
     * @return the platforms this metrostation holds
     *
    \n REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
     */
    std::vector<Platform*> getPlatforms() const;

    /**
     * @brief finds the platform with the specified platformNumber and returns it
     * @param platformNumber: the platform number of the station
     *
     \n REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
     \n REQUIRE(platformNumber > 0, "The given platformNumber must be greater than 0!");
     */
    Platform* getPlatform(int platformNumber);

    /**
     * @brief adds a platform to the list of platforms of this metronet
     * @param platform: the platform to add to the metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
     */
    void addPlatform(Platform* platform);

    /**
     * @return the type of the platform (Underground for a metrostation)
     */
    StationType getType() const { return UNDERGROUND; };

};