//
// Created by rob on 27/02/2020.
//

#include "Tram.h"
#include "TrackNode.h"

Tram::Tram(int line, TrackNode* beginNode, double maxSpeed, int amountOfSeats, double length, const std::string& type) :
        m_tramLine(line),
        m_currentSpeed(maxSpeed),
        m_amountOfSeats(amountOfSeats),
        m_beginNode(beginNode),
        m_currentNode(beginNode),
        LENGTH(length),
        MAX_SPEED(maxSpeed),
        TYPE(type) {
    Tram::_initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Tram::~Tram() {}

const TrackNode* Tram::getBeginNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_beginNode;
}

const TrackNode* Tram::getCurrentNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentNode;
}

int Tram::getTramLine() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_tramLine;
}

double Tram::getCurrentSpeed() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentSpeed;
}

int Tram::getAmountOfSeats() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_amountOfSeats;
}

void Tram::setCurrentSpeed(int currentSpeed) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    Tram::m_currentSpeed = currentSpeed;
}

void Tram::updateLocation() {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    m_currentNode = m_currentNode->getNextNode();
}

bool Tram::properlyInitialized() const {
    return _initCheck == this;
}