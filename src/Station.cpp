//
// Created by jasper on 27/02/2020.
//

#include "Station.h"
#include "Track.h"

Station::~Station() {}

const string& Station::getName() const {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    ENSURE(m_name.length()>0,"Name can't be the empty string.");
    return m_name;
}

void Station::setName(const string& name) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(name.length()>0,"Name can't be the empty string.");
    Station::m_name = name;
}

Track* Station::getTrack(int line) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(line>=0,"Line must be a positive number.");
    for (vector<Track*>::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        if ((*it)->getLine() == line) {
            return (*it);
        }
    }

    return NULL;
}

void Station::addTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(track->properlyInitialized(), "Track cannot be NULL.");
    m_tracks.push_back(track);
}

Station::Station() {
    Station::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

bool Station::properlyInitialized() const {
    return _initCheck == this;
}
