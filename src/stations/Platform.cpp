//
// Created by thibaultpoels on 09/04/2020.
//

#include <trams/Tram.h>
#include "Platform.h"
#include "Station.h"
#include "Track.h"

Platform::Platform(Station* station, int number) :
        m_station(station),
        m_number(number),
        m_currentTram(NULL) {
    Platform::_initCheck = this;
    m_currentTrackIndex = 0;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Platform::Platform(int number) :
        m_number(number),
        m_currentTram(NULL) {
    Platform::_initCheck = this;
    m_currentTrackIndex = 0;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

vector<Track*>& Platform::getOutgoingTracks() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_outgoingTracks;
}

void Platform::addOutgoingTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_outgoingTracks.push_back(track);
}

vector<Track*>& Platform::getIncomingTracks() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_incomingTracks;
}

void Platform::addIncomingTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_incomingTracks.push_back(track);
}

Station* Platform::getStation() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_station;
}

void Platform::setStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_station = station;
}

int Platform::getNumber() const {
    return m_number;
}

void Platform::setNumber(int number) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_number = number;
}

void Platform::setCurrentTram(Tram* currentTram) {
    REQUIRE(!m_currentTram, " cannot set current tram: this platform already has a tram on it!");
    m_currentTram = currentTram;
}

Tram* Platform::getCurrentTram() const {
    return m_currentTram;
}

bool Platform::hasCurrentTram() const {
    return getCurrentTram() != NULL;
}

unsigned int Platform::getNextTrackIndex(unsigned int currentTrackIndex) {
    if (currentTrackIndex == m_incomingTracks.size() - 1) {
        return 0;
    } else {
        return currentTrackIndex + 1;
    }
}

bool Platform::properlyInitialized() {
    return Platform::_initCheck == this;
}

bool Platform::canReceiveNewIncomingTram() const {
    if (!getCurrentTram()) {
        // Check if there is currently a tram directly heading to this platform (so no tram which is going to a queue via a stopSignal)
        for (std::vector<Track*>::const_iterator trackIt = m_incomingTracks.begin(); trackIt < m_incomingTracks.end(); trackIt++) {
            if (!(*trackIt)->getStopSignal()) {
                if ((*trackIt)->getAmountOfTrams() > 0) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

// Omdat je zo nog steeds een eerlijke verdeling hebt tussen trams die mogen vertrekken
void Platform::receiveNewIncomingTram() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member variables.");
    REQUIRE(!m_incomingTracks.empty(), "This method should not be called if it cannot be reached by a track");
    REQUIRE(canReceiveNewIncomingTram(), "This platform cannot receive a new incoming tram yet!");

    unsigned int trackIndexToCheck = m_currentTrackIndex;
    bool success = false;
    do {

        Track* trackToCheck = m_incomingTracks.at(trackIndexToCheck);
        if (trackToCheck->getStopSignal()) {
            std::queue<Tram*>& waitingTrams = m_incomingTracks.at(trackIndexToCheck)->getWaitingTrams();
            if (!waitingTrams.empty()) {
                m_currentTram = waitingTrams.front();
                waitingTrams.pop();
                m_currentTram->putOnPlatform(this);
                success = true;
            }
        } else {
            Tram* tramToReceive = trackToCheck->getSourcePlatform()->getCurrentTram();
            if (tramToReceive) {
                tramToReceive->putOnTrack(trackToCheck);
            }
        }

        trackIndexToCheck = getNextTrackIndex(trackIndexToCheck);
    } while (!success && trackIndexToCheck != m_currentTrackIndex);
}