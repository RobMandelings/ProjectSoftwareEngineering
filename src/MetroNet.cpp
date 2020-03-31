//
// Created by thibaultpoels on 27/02/2020.
//

#include "library.h"
#include "MetroNet.h"
#include "trams/Tram.h"
#include "Track.h"
#include "Station.h"
#include "DesignByContract.h"

MetroNet::MetroNet(const string& name) :
        m_name(name) {
    MetroNet::_initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

MetroNet::~MetroNet() {

    //Delete all the stations of this metronet
    for (vector<Station*>::iterator it = m_stations.begin(); it < m_stations.end(); it++) {
        delete *it;
    }

    //Delete all the tracks of this metronet
    for (vector<Track*>::iterator it = m_tracks.begin(); it < m_tracks.end(); it++) {
        delete *it;
    }

    //Delete all the trams of this metronet
    for (vector<Tram*>::iterator it = m_trams.begin(); it < m_trams.end(); it++) {

        delete *it;
    }
}

const string& MetroNet::getName() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_name;
}

Tram* MetroNet::getTram(int line) const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    for (unsigned int i = 0; i < MetroNet::m_trams.size(); i++) {
        if (MetroNet::m_trams[i]->getTramLine() == line) {
            return MetroNet::m_trams[i];
        }
    }
    return NULL;
}


Station* MetroNet::getStation(const char* name) const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
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

const vector<Track*>& MetroNet::getTracks() const {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    return m_tracks;
}

void MetroNet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    MetroNet::m_trams.push_back(tram);
}

void MetroNet::addStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    MetroNet::m_stations.push_back(station);
}

void MetroNet::addTrack(Track* track) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    m_tracks.push_back(track);
}

Track* MetroNet::getTrack(int line) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    for (vector<Track*>::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        if ((*it)->getLine() == line) {
            return (*it);
        }
    }

    return NULL;
}

void MetroNet::updateTramLocations() {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");

    std::ofstream outfile;
    outfile.open("../output/events.metro", std::ios::app);

    for (vector<Tram*>::iterator it = m_trams.begin(); it != m_trams.end(); ++it) {
        Tram& tram = **it;
        tram.updateLocation();

        outfile << "Tram " << tram.getTramLine() << " ging van station " << tram.getCurrentNode()->getPreviousNode()->getStation()->getName() << " naar station " << tram.getCurrentNode()->getStation()->getName() << "\n";

    }

    outfile.close();
}

bool MetroNet::properlyInitialized() const {
    return _initCheck == this;
}
