//
// Created by thibaultpoels on 09/04/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_PERRON_H
#define PROJECTSOFTWAREENGINEERING_PERRON_H

#include "library.h"

class Station;
class Track;

class Platform {

private:

    Station* m_station;

    int m_number;

    vector<Track*> m_tracks;

    Platform* _initCheck;

public:

    Platform(Station* station, int number);

    Platform(int number);

    vector<Track*>& getTracks();

    void addTrack(Track* track);

    void setTracks(const vector<Track*>& tracks);

    Station *getStation();

    void setStation(Station *station);

    int getNumber() const;

    void setNumber(int number);

    bool properlyInitialized();

};


#endif //PROJECTSOFTWAREENGINEERING_PERRON_H
