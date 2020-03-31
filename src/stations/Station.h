//
// Created by jasper on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATION_H
#define PROJECTSOFTWAREENGINEERING_STATION_H

#include "library.h"

class Track;

class Station {
private:
    string m_name;
    vector<Track*> m_tracks;
    Station* _initCheck;
public:

    virtual ~Station();

    explicit Station();

    virtual const char* getType() const = 0;

    /**
     * @brief Simple getter
     * @return the name of this station
     */
    const string& getName() const;

    /**
     * @brief sets the name of this station
     * @param name: the name you want to set this station to
     */
    void setName(const string& name);

    /**
     * @brief gets a track corresponding to the line given
     * @return the track
     */
    Track* getTrack(int line);

    /**
     * @brief adds a track to the list of tracks in this station
     */
    void addTrack(Track* track);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};


#endif //PROJECTSOFTWAREENGINEERING_STATION_H
