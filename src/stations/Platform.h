//
// Created by thibaultpoels on 09/04/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_PERRON_H
#define PROJECTSOFTWAREENGINEERING_PERRON_H

#include "Direction.h"
#include "library.h"

class Station;
class Track;
class Tram;

class Platform {

private:

    Station* m_station;

    int m_number;

    unsigned int m_currentTrackIndex;

    vector<Track*> m_outgoingTracks;

    vector<Track*> m_incomingTracks;

    Tram* m_currentTram;

    Platform* _initCheck;

public:

    Platform(Station* station, int number);

    explicit Platform(int number);

    vector<Track*>& getOutgoingTracks();

    void addOutgoingTrack(Track* track);

    vector<Track*>& getIncomingTracks();

    void addIncomingTrack(Track* track);

    Station *getStation();

    void setStation(Station *station);

    int getNumber() const;

    void setNumber(int number);

    void setCurrentTram(Tram* currentTram);

    void removeCurrentTram();

    Tram* getCurrentTram() const;

    bool hasCurrentTram() const;

    bool canReceiveNewIncomingTram() const;

    void receiveNewIncomingTram();

    unsigned int getNextTrackIndex(unsigned int currentTrackIndex);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};

std::ostream& operator<<(std::ostream& os, Platform& platform);

std::ostream& operator<<(std::ostream& os, Platform* platform);


#endif //PROJECTSOFTWAREENGINEERING_PERRON_H
