//
// Created by thibaultpoels on 09/04/2020.
//

#include "Platform.h"
#include "Station.h"
#include "Track.h"

Platform::Platform(Station *station, int number) :m_station(station), m_number(number){
    Platform::_initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Platform::Platform(int number) : m_number(number){
    Platform::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

vector<Track*>& Platform::getTracks() {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    return m_tracks;
}

void Platform::setTracks(const vector<Track*> &tracks) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_tracks = tracks;
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

void Platform::addTrack(Track *track) {
    REQUIRE(this->properlyInitialized(), "Platform must be properly initialized to use its member methods.");
    m_tracks.push_back(track);
}

bool Platform::properlyInitialized() {
    return Platform::_initCheck == this;
}


