//
// Created by thibaultpoels on 09/04/2020.
//

#include "Platform.h"
#include "Station.h"
#include "Track.h"

Platform::Platform(Station* station, int number) :
        m_station(station),
        m_number(number),
        m_currentTram(NULL) {
    Platform::_initCheck = this;
    nextTrackIndex = 0;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Platform::Platform(int number) :
        m_number(number),
        m_currentTram(NULL) {
    Platform::_initCheck = this;
    nextTrackIndex = 0;
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

bool Platform::properlyInitialized() {
    return Platform::_initCheck == this;
}

void Platform::getIncomingTram() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member variables.");
    m_currentTram = m_incomingTracks[nextTrackIndex]->getWaitingTrams().front();
    m_incomingTracks[nextTrackIndex]->getWaitingTrams().pop();
    m_incomingTracks[nextTrackIndex]->deleteTram();

    if(nextTrackIndex == m_incomingTracks.size()-1){
        nextTrackIndex = 0;
    } else {
        nextTrackIndex++;
    }
}
