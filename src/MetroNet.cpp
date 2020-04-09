//
// Created by thibaultpoels on 27/02/2020.
//

#include "library.h"
#include "MetroNet.h"
#include "trams/Tram.h"
#include "lines/Line.h"
#include "Station.h"
#include "DesignByContract.h"

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

void MetroNet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(tram != NULL && tram->properlyInitialized(), "Tram cannot be NULL.");
    REQUIRE(this->checkVehicleNumberAvailability(tram), "Tram number must be available in this line.");
    MetroNet::m_trams.push_back(tram);
}

void MetroNet::addStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(station != NULL && station->properlyInitialized(), "Station cannot be NULL.");
    MetroNet::m_stations.push_back(station);
}

void MetroNet::addLine(Line* line) {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
    REQUIRE(line != NULL && line->properlyInitialized(), "Line cannot be NULL.");
    m_lines.push_back(line);
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

void MetroNet::updateTramLocations() {
    REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");

    std::ofstream outfile;
    outfile.open("../output/events.metro", std::ios::app);

    for (vector<Tram*>::iterator it = m_trams.begin(); it != m_trams.end(); ++it) {
        Tram& tram = **it;
        tram.update(0);

        outfile << "Tram " << tram.getTramLine()->getLineNumber() << " (" << tram.getVehicleNumber() << ")" << " ging van station "
                << tram.getCurrentNode()->getPreviousNode()->getStation()->getName() << " naar station " << tram.getCurrentNode()->getStation()->getName() << "\n";


    }

    outfile.close();
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
