//
// Created by thibaultpoels on 09/04/2020.
//

#include <trams/Tram.h>
#include "Platform.h"
#include "Station.h"
#include "Track.h"
#include "FileHandler.h"
#include "SimulationTime.h"

Platform::Platform(Station* station, int number) :
        m_station(station),
        m_number(number),
        m_currentTram(NULL) {
    Platform::_initCheck = this;
    m_currentTrackIndex = 0;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Platform::Platform(int number) :
        m_station(NULL),
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

void Platform::addOutgoingTrack(Track* outgoingTrack) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    
    unsigned int oldSize = m_outgoingTracks.size();
    
    m_outgoingTracks.push_back(outgoingTrack);
    
    ENSURE(m_outgoingTracks.size()>oldSize, "An outgoing track must be added after addOutgoingTrack is called.");
}

vector<Track*>& Platform::getIncomingTracks() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_incomingTracks;
}

void Platform::addIncomingTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    
    unsigned int oldSize = m_incomingTracks.size();
    
    m_incomingTracks.push_back(track);
    
    ENSURE(m_incomingTracks.size()>oldSize, "An incoming track must be added after addIncomingTrack is called.");
}

Station* Platform::getStation() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_station;
}

void Platform::setStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    REQUIRE(station, "The station given can not be NULL");
    REQUIRE(!m_station, "A station is already set on this platform");
    m_station = station;
    ENSURE(m_station == station, "Station must be set properly.");
}

int Platform::getNumber() const {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    REQUIRE(m_number >= 0, "The platform number must be >= 0");
    return m_number;
}


void Platform::setCurrentTram(Tram* currentTram) {
    REQUIRE(currentTram != NULL, "The given tram should not be NULL");
    REQUIRE(!m_currentTram, " cannot set current tram: this platform already has a tram on it!");
    m_currentTram = currentTram;
    ENSURE(m_currentTram == currentTram, "Current tram must be set properly.");
}

void Platform::removeCurrentTram() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_currentTram = NULL;
    ENSURE(m_currentTram == NULL, "Current tram must be removed properly.");
}

Tram* Platform::getCurrentTram() const {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_currentTram;
}

bool Platform::hasCurrentTram() const {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return getCurrentTram();
}

unsigned int Platform::getNextTrackIndex(unsigned int currentTrackIndex) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    REQUIRE(currentTrackIndex >= 0, "The track index given must be >= 0!");
    if (currentTrackIndex == m_incomingTracks.size() - 1) {
        return 0;
    } else {
        return currentTrackIndex + 1;
    }
}

bool Platform::canReceiveNewIncomingTram() const {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");

    if (!getCurrentTram() && !m_incomingTracks.empty()) {
        // Check if there is currently a tram directly heading to this platform (so no tram which is going to a queue via a stopSignal)
        for (std::vector<Track*>::const_iterator trackIt = m_incomingTracks.begin(); trackIt < m_incomingTracks.end(); trackIt++) {
            if (!(*trackIt)->getStopSignal()) {
                if ((*trackIt)->hasRidingTram()) {
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
    REQUIRE(canReceiveNewIncomingTram(), "This platform cannot receive a new incoming tram yet!");
    REQUIRE(m_currentTrackIndex >= 0, "The current track index is less than 0, this should not be possible");

    unsigned int trackIndexToCheck = m_currentTrackIndex;
    bool success = false;
    do {

        Track* trackToCheck = m_incomingTracks.at(trackIndexToCheck);
        if (trackToCheck->getStopSignal()) {
            std::deque<Tram*>& waitingTrams = m_incomingTracks.at(trackIndexToCheck)->getWaitingTrams();
            if (!waitingTrams.empty()) {
                m_currentTram = waitingTrams.front();
                waitingTrams.pop_front();
                m_currentTram->putOnPlatform(this);
                FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Tram " << m_currentTram << " arrived at " << this << std::endl;
                success = true;
            }
        } else {
            Tram* tramToReceive = trackToCheck->getSourcePlatform()->getCurrentTram();
            if (tramToReceive && tramToReceive->getCurrentWaitTime() <= 0) {

                canReceiveNewIncomingTram();
                tramToReceive->putOnTrack(trackToCheck);
                success = true;
                FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Tram " << tramToReceive << " going to " << this << std::endl;
            }
        }

        trackIndexToCheck = getNextTrackIndex(trackIndexToCheck);
    } while (!success && trackIndexToCheck != m_currentTrackIndex);

    m_currentTrackIndex = getNextTrackIndex(m_currentTrackIndex);
    
    ENSURE(success || trackIndexToCheck == m_currentTrackIndex, "After receiveNewIncomingTram is called, it shouldn't be able to receive again.");
}

std::ostream& operator<<(ostream& os, Platform& platform) {
    return os << "Station " << platform.getStation() << ", platform " << platform.getNumber() << "";
}

std::ostream& operator<<(ostream& os, Platform* platform) {
    return os << *platform;
}

bool Platform::properlyInitialized() const {
    return Platform::_initCheck == this;
}