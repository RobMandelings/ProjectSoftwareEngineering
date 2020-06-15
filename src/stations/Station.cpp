//
// Created by jasper on 27/02/2020.
//

#include "Station.h"
#include "Line.h"
#include "Tram.h"
#include "TramStop.h"
#include "Platform.h"
#include "MetroStation.h"

const string& Station::getName() const {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    ENSURE(m_name.length() > 0, "Name can't be the empty string.");
    return m_name;
}

void Station::setName(const string& name) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(name.length() > 0, "Name can't be the empty string.");
    Station::m_name = name;
    ENSURE(m_name == name, "m_name has to be set to name.");
}

Line* Station::getLine(int line) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(line >= 0, "Line must be a positive number.");
    for (vector<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); ++it) {
        if ((*it)->getLineNumber() == line) {
            return (*it);
        }
    }

    return NULL;
}

void Station::addLine(Line* line) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(line != NULL && line->properlyInitialized(), "Line cannot be NULL.");
    
    unsigned int oldSize = m_lines.size();
    
    m_lines.push_back(line);
    
    ENSURE(m_lines.size()>oldSize,"A line must be added after addLine is called.");
}

Station::Station() {
    Station::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Station::~Station() {}

TramStop::TramStop(Platform* platform) :
        m_platformHeen(platform),
        m_platformTerug(new Platform(platform->getStation(), platform->getNumber())){
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Platform* TramStop::getPlatformTo() const {
    REQUIRE(this->properlyInitialized(), "TramStop must be initialized before its member variables are used.");
    return m_platformHeen;
}

Platform* TramStop::getPlatformFrom() const {
    REQUIRE(this->properlyInitialized(), "TramStop must be initialized before its member variables are used.");
    return m_platformTerug;
}

void MetroStation::addPlatform(Platform* platform) {
    REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
    
    unsigned int oldSize = m_platforms.size();
    
    m_platforms.push_back(platform);
    
    ENSURE(m_platforms.size()>oldSize,"A platform must be added after addPlatform is called.");
}

Platform* MetroStation::getPlatform(int platformNumber) {
    REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
    REQUIRE(platformNumber > 0, "The given platformNumber must be greater than 0!");
    for (std::vector<Platform*>::iterator platformIt = m_platforms.begin(); platformIt < m_platforms.end(); platformIt++) {
        if ((*platformIt)->getNumber() == platformNumber) {
            return *platformIt;
        }
    }
    return NULL;
}

std::vector<Platform*> MetroStation::getPlatforms() const {
    REQUIRE(this->properlyInitialized(), "MetroStation must be initialized before its member variables are used.");
    return m_platforms;
}

bool Station::properlyInitialized() const {
    return _initCheck == this;
}

std::ostream& operator<<(ostream& os, Station& station) {
    return os << station.getName();
}

std::ostream& operator<<(ostream& os, Station* station) {
    return os << *station;
}