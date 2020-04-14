//
// Created by thibaultpoels on 09/04/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_PERRON_H
#define PROJECTSOFTWAREENGINEERING_PERRON_H

#include "enums.h"
#include "library.h"

class Station;
class Track;
class Tram;

class Platform {

private:

    Direction m_direction;

    Station* m_station;

    int m_number;

    vector<Track*> m_outgoingTracks;
    vector<Track*> m_incomingTracks;

    Tram* m_currentTram;

    Platform* _initCheck;

public:

    Platform(Station* station, int number, Direction direction);

    Platform(int number, Direction direction);

    Direction getDirection() const;

    vector<Track*>& getOutgoingTracks();

    void addOutgoingTrack(Track* track);

    vector<Track*>& getIncomingTracks();

    void addIncomingTrack(Track* track);

    Station *getStation();

    void setStation(Station *station);

    int getNumber() const;

    void setNumber(int number);

    void setCurrentTram(Tram* currentTram);

    Tram* getCurrentTram() const;

    bool hasCurrentTram() const;

    bool properlyInitialized();

};


#endif //PROJECTSOFTWAREENGINEERING_PERRON_H
