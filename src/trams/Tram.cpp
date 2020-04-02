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
    ENSURE(m_tramLine>=0, "Line must be a positive number.");
    ENSURE(MAX_SPEED>=0, "Speed cannot be negative.");
    ENSURE(m_amountOfSeats>=0,"The amount of seats cannot be negative.");
    ENSURE(m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Tram::~Tram() {}

const TrackNode* Tram::getBeginNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    return m_beginNode;
}

const TrackNode* Tram::getCurrentNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE( m_currentNode!=NULL && m_currentNode->properlyInitialized(),"The current node cannot be NULL.");
    return m_currentNode;
}

int Tram::getTramLine() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE(m_tramLine>=0,"Line must be a positive number.");
    return m_tramLine;
}

double Tram::getCurrentSpeed() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE(m_currentSpeed>=0,"Speed cannot be negative.");
    return m_currentSpeed;
}

int Tram::getAmountOfSeats() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE(m_amountOfSeats>=0,"Amount of seats cannot be negative.");
    return m_amountOfSeats;
}

void Tram::setCurrentSpeed(int currentSpeed) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_amountOfSeats>=0,"Amount of seats cannot be negative.");
    Tram::m_currentSpeed = currentSpeed;
}

void Tram::updateLocation() {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    ENSURE(m_currentNode != NULL && m_currentNode->properlyInitialized(), "Current node cannot be NULL.");
    m_currentNode = m_currentNode->getNextNode();
}

bool Tram::properlyInitialized() const {
    return _initCheck == this;
}