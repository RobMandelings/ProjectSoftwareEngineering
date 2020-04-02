//
// Created by jasper on 27/02/2020.
//

#include "Station.h"
#include "lines/Line.h"

const string& Station::getName() const {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    ENSURE(m_name.length()>0,"Name can't be the empty string.");
    return m_name;
}

void Station::setName(const string& name) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(name.length()>0,"Name can't be the empty string.");
    Station::m_name = name;
    ENSURE(m_name==name,"m_name has to be set to name.");
}

Line* Station::getLine(int line) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(line>=0,"Line must be a positive number.");
    for (vector<Line*>::iterator it = m_lines.begin(); it != m_lines.end(); ++it) {
        if ((*it)->getLine() == line) {
            return (*it);
        }
    }

    return NULL;
}

void Station::addLine(Line* line) {
    REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
    REQUIRE(line!=NULL && line->properlyInitialized(), "Line cannot be NULL.");
    m_lines.push_back(line);
}

bool Station::properlyInitialized() const {
    return _initCheck == this;
}

Station::Station() {
    Station::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Station::~Station() {

}