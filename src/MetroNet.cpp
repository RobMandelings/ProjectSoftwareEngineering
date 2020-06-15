//
// Created by thibaultpoels on 27/02/2020.
//

#include "library.h"
#include "MetroNet.h"
#include "trams/Tram.h"
#include "lines/Line.h"
#include "Station.h"
#include "TramStop.h"
#include "MetroStation.h"
#include "Track.h"
#include "DesignByContract.h"
#include "FileHandler.h"

MetroNet::MetroNet(const string& name) :
        m_name(name) {
    MetroNet::_initCheck = this;
    ENSURE(m_name.length() > 0, "Name can't be the empty string.");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

MetroNet::~MetroNet() {

    //Delete all the stations of this metronet
    for (vector<Station*>::iterator it = m_stations.begin(); it < m_stations.end(); it++) {
        delete *it;
    }

    //Delete all the lines of this metronet
    for (vector<Line*>::iterator it = m_lines.begin(); it < m_lines.end(); it++) {
        delete *it;
    }

    //Delete all the trams of this metronet
    for (vector<Tram*>::iterator it = m_trams.begin(); it < m_trams.end(); it++) {

        delete *it;
    }

    // TODO delete tracks
}

const string& MetroNet::getName() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(m_name.length() > 0, "Name can't be the empty string.");
    return m_name;
}

Station* MetroNet::getStation(const char* name) const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(name != NULL, "Name cannot be empty.");
    for (unsigned int i = 0; i < MetroNet::m_stations.size(); i++) {
        if (MetroNet::m_stations[i]->getName() == name) {
            return MetroNet::m_stations[i];
        }
    }
    return NULL;
}

const vector<Tram*>& MetroNet::getTrams() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_trams;
}

const vector<Station*>& MetroNet::getStations() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_stations;
}

const vector<Line*>& MetroNet::getLines() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_lines;
}

const vector<Track*>& MetroNet::getTracks() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_tracks;
}

Track* MetroNet::getTrack(Platform* sourcePlatform, Platform* destinationPlatform) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    for (vector<Track*>::iterator it = m_tracks.begin(); it < m_tracks.end(); it++) {
        Track* track = *it;
        if (track->getSourcePlatform() == sourcePlatform && track->getDestinationPlatform() == destinationPlatform) {
            return track;
        }
    }
    return NULL;
}

bool MetroNet::hasTrack(Platform* sourcePlatform, Platform* destinationPlatform) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return getTrack(sourcePlatform, destinationPlatform);
}

void MetroNet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(tram != NULL && tram->properlyInitialized(), "Tram cannot be NULL.");
    REQUIRE(this->checkVehicleNumberAvailability(tram), "Tram number must be available in this line.");
    
    unsigned int oldSize = m_trams.size();
    
    MetroNet::m_trams.push_back(tram);
    
    ENSURE(m_trams.size()>oldSize, "A tram must be added after addTram is called.");
}

void MetroNet::addStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(station != NULL && station->properlyInitialized(), "Station cannot be NULL.");

    unsigned int oldSize = m_stations.size();
    
    MetroNet::m_stations.push_back(station);

    ENSURE(m_stations.size()>oldSize, "A station must be added after addStation is called.");
}

void MetroNet::addLine(Line* line) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(line != NULL && line->properlyInitialized(), "Line cannot be NULL.");
    REQUIRE(!getLine(line->getLineNumber()), "A line with this number already exists with this number");
    
    unsigned int oldSize = m_lines.size();
    
    m_lines.push_back(line);

    ENSURE(m_lines.size()>oldSize, "A line must be added after addLine is called.");
}

void MetroNet::addTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(track != NULL && track->properlyInitialized(), "Track cannot be NULL.");
    
    unsigned int oldSize = m_tracks.size();
    
    m_tracks.push_back(track);
    
    ENSURE(m_tracks.size()>oldSize,"A track must be added after addTrack is called.");
}

Line* MetroNet::getLine(int line) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(line >= 0, "Line must be a positive number.");
    for (vector<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); ++it) {
        if ((*it)->getLineNumber() == line) {
            return (*it);
        }
    }
    return NULL;
}

void MetroNet::updateTrams(bool debug) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");

    for (vector<Tram*>::iterator it = m_trams.begin(); it != m_trams.end(); ++it) {
        Tram& tram = **it;
        tram.update(debug);
    }
}

bool MetroNet::properlyInitialized() const {
    return _initCheck == this;
}

bool MetroNet::checkVehicleNumberAvailability(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    for (unsigned int i = 0; i < m_trams.size(); i++) {
        if (m_trams[i]->getTramLine()->getLineNumber() == tram->getTramLine()->getLineNumber()) {
            if (m_trams[i]->getVehicleNumber() == tram->getVehicleNumber()) {
                return false;
            }
        }
    }

    return true;
}
