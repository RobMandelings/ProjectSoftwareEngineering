//
// Created by jasper on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATION_H
#define PROJECTSOFTWAREENGINEERING_STATION_H

#include "library.h"

class Track;

enum StationType {
    ABOVE_GROUND,
    UNDERGROUND
};

class Station {

private:
    string m_name;
    vector<Track*> m_tracks;
    Station* _initCheck;
    StationType m_stationType;

public:

    virtual ~Station();


    /**
     * Constructor
     * @param stationType
     *
     \n ENSURE(this->properlyInitialized(), "Constructor must end ...");
     */
    explicit Station(StationType stationType);

    /**
     * @return station type
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     */
    StationType getType() const;

    /**
     * @brief Simple getter
     * @return the name of this station
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n ENSURE(m_name.length()>0,"Name can't be the empty string.");
     */
    const string& getName() const;

    /**
     * @brief sets the name of this station
     * @param name: the name you want to set this station to
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(name.length()>0,"Name can't be the empty string.");
     */
    void setName(const string& name);

    /**
     * @brief gets a track corresponding to the line given
     * @return the track
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     */
    Track* getTrack(int line);

    /**
     * @brief adds a track to the list of tracks in this station
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(track->properlyInitialized(), "Track cannot be NULL.");
     */
    void addTrack(Track* track);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};


#endif //PROJECTSOFTWAREENGINEERING_STATION_H
