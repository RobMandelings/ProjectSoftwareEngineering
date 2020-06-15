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

    /** The (parent) station belonging to this platform */
    Station* m_station;

    /** The platform number, used to identify the platform within a station */
    int m_number;

    /**
     * The current track index keeps track of the currentTrack it will query a tram for.
     * This enhances fairly distribution among leaving trams (in case of a longer queue)
     */
    unsigned int m_currentTrackIndex;

    /** The outgoing tracks of the platform */
    vector<Track*> m_outgoingTracks;

    /** The incoming tracks of the platform */
    vector<Track*> m_incomingTracks;

    /** The tram currently staying on this platform */
    Tram* m_currentTram;

    Platform* _initCheck;

public:

    /**
     * @brief simple constructor
     * @param station: the station belonging to the platform
     * @param number: the platformNumber of this platform
     */
    Platform(Station* station, int number);

    /**
     * @brief simple constructor
     * @param number: the platformNumber of this platform
     */
    explicit Platform(int number);

    /**
     * @return the tracks which leave the platform for another platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    vector<Track*>& getOutgoingTracks();

    /**
     * @return the tracks which enter this platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    vector<Track*>& getIncomingTracks();

    /**
     * @brief adds an outgoing track to this platform
     * @param outgoingTrack: the outgoing track to add
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n ENSURE(m_outgoingTracks.size()>oldSize, "An outgoing track must be added after addOutgoingTrack is called.");
     */
    void addOutgoingTrack(Track* outgoingTrack);

    /**
     * @brief adds an incoming track to this platform
     * @param incomingTrack: the incoming track to add
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n ENSURE(m_incomingTracks.size()>oldSize, "An incoming track must be added after addIncomingTrack is called.");
     */
    void addIncomingTrack(Track* track);

    /**
     * @brief simple getter
     * @return the station this platform belongs to
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    Station* getStation();

    /**
     * @brief simple setter
     * @param station: the station this platform belongs to
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n REQUIRE(station, "The station given can not be NULL");
     \n REQUIRE(!m_station, "A station is already set on this platform");
     \n ENSURE(m_station == station, "Station must be set properly.");
     */
    void setStation(Station* station);

    /**
     * @brief simple getter
     * @return the platform number of the platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n REQUIRE(m_number >= 0, "The platform number must be >= 0");
     */
    int getNumber() const;

    /**
     * @brief simple setter
     * @param currentTram: the current tram to set it to
     \n REQUIRE(currentTram != NULL, "The given tram should not be NULL");
     \n REQUIRE(!m_currentTram, " cannot set current tram: this platform already has a tram on it!");
     \n ENSURE(m_currentTram == currentTram, "Current tram must be set properly.");
     */
    void setCurrentTram(Tram* currentTram);

    /**
     * @brief removes the current tram from the platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n ENSURE(m_currentTram == NULL, "Current tram must be removed properly.");
     */
    void removeCurrentTram();

    /**
     * @brief simple getter
     * @return the current tram staying on the platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    Tram* getCurrentTram() const;

    /**
     * @brief checks if there is a tram currently staying on the platform
     * @return true if there is a tram staying on the platform, false if not
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    bool hasCurrentTram() const;

    /**
     * @brief checks if the tram can receive a new tram, conditions: no tram is currently on their way to this track, no tram is currently staying on the track
     * @return true if the platform can receive a new tram on the platform
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     */
    bool canReceiveNewIncomingTram() const;

    /**
     * @brief receive a new tram on this platform (let a tram leave its previous platform)
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member variables.");
     \n REQUIRE(canReceiveNewIncomingTram(), "This platform cannot receive a new incoming tram yet!");
     \n REQUIRE(m_currentTrackIndex >= 0, "The current track index is less than 0, this should not be possible");
     \n ENSURE(!canReceiveNewIncomingTram(), "After receiveNewIncomingTram is called it shouldn't be able to receive again.");
     */
    void receiveNewIncomingTram();

    /**
     * @brief checks what the next track index should be and update it accordingly
     * @param currentTrackIndex: the current track index given
     * @return the new trackIndex
     \n REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
     \n REQUIRE(currentTrackIndex >= 0, "The track index given must be >= 0!");
     */
    unsigned int getNextTrackIndex(unsigned int currentTrackIndex);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};

std::ostream& operator<<(std::ostream& os, Platform& platform);

std::ostream& operator<<(std::ostream& os, Platform* platform);


#endif //PROJECTSOFTWAREENGINEERING_PERRON_H
