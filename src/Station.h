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
public:
    const string& getName() const;

    void setName(const string& name);

    Track* getTrack(int number);

    void addTrack(Track* track);

};


#endif //PROJECTSOFTWAREENGINEERING_STATION_H
