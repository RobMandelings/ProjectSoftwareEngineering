//
// Created by thibaultpoels on 27/02/2020.
//

#include "MetroNet.h"
#include "Tram.h"
#include "Track.h"
#include "Station.h"

MetroNet::MetroNet(const string& name) :
        m_name(name) {}

const string& MetroNet::getName() const {
    return m_name;
}

Tram* MetroNet::getTram(int line) const {
    for (unsigned int i = 0; i < MetroNet::m_trams.size(); i++) {
        if (MetroNet::m_trams[i]->getTramLine() == line) {
            return MetroNet::m_trams[i];
        }
    }
    return NULL;
}


Station* MetroNet::getStation(const char* name) const {
    for (unsigned int i = 0; i < MetroNet::m_stations.size(); i++) {
        if (MetroNet::m_stations[i]->getName() == name) {
            return MetroNet::m_stations[i];
        }
    }
    return NULL;
}

const vector<Tram*>& MetroNet::getTrams() const {
    return m_trams;
}

const vector<Station*>& MetroNet::getStations() const {
    return m_stations;
}

const vector<Track*>& MetroNet::getTracks() const {
    return m_tracks;
}

void MetroNet::addTram(Tram* tram) {
    MetroNet::m_trams.push_back(tram);
}

void MetroNet::addStation(Station* station) {
    MetroNet::m_stations.push_back(station);
}

void MetroNet::addTrack(Track* track) {
    m_tracks.push_back(track);
}

Track* MetroNet::getTrack(int line) {
    for (vector<Track*>::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        if ((*it)->getLine() == line) {
            return (*it);
        }
    }

    return NULL;
}

void MetroNet::updateTramLocations() {

    for (vector<Tram*>::iterator it = m_trams.begin(); it != m_trams.end(); ++it) {
        Tram& tram = **it;
        tram.updateLocation();
        std::cout << "Tram " << tram.getTramLine() << " ging van station " << tram.getCurrentNode()->getPreviousNode()->getStation()->getName() << " naar station " << tram.getCurrentNode()->getStation()->getName() << endl;
    }

    cout << endl;
}