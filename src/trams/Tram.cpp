//
// Created by rob on 27/02/2020.
//

#include "Tram.h"
#include "lines/LineNode.h"

Tram::Tram(Line* line, Station* beginStation, double maxSpeed, int amountOfSeats, int vehicleNumber,double length, const std::string& type) :
        m_tramLine(line),
        m_currentSpeed(maxSpeed),
        m_amountOfSeats(amountOfSeats),
        m_vehicleNumber(vehicleNumber),
        m_beginNode(line->getNodeForStation(beginStation)),
        m_currentNode(line->getNodeForStation(beginStation)),
        LENGTH(length),
        MAX_SPEED(maxSpeed),
        TYPE(type) {
    Tram::_initCheck = this;
    ENSURE(line->getNodeForStation(beginStation) != NULL, "Tram constructor: the begin station given is not within the line!");
    ENSURE(m_tramLine != NULL, "Line must be a positive number.");
    ENSURE(MAX_SPEED>=0, "Speed cannot be negative.");
    ENSURE(m_amountOfSeats>=0,"The amount of seats cannot be negative.");
    ENSURE(m_vehicleNumber>=0,"Vehicle number must be a positive number.");
    ENSURE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Tram::~Tram() {}

const LineNode* Tram::getBeginNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    return m_beginNode;
}

const LineNode* Tram::getCurrentNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE( m_currentNode!=NULL && m_currentNode->properlyInitialized(),"The current node cannot be NULL.");
    return m_currentNode;
}

Line* Tram::getTramLine() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_tramLine != NULL,"The tram line should not be a nullptr");
    return m_tramLine;
}

double Tram::getCurrentSpeed() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_currentSpeed>=0,"Speed cannot be negative.");
    return m_currentSpeed;
}

int Tram::getAmountOfSeats() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_amountOfSeats>=0,"Amount of seats cannot be negative.");
    return m_amountOfSeats;
}

void Tram::setCurrentSpeed(int currentSpeed) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(currentSpeed>=0,"Amount of seats cannot be negative.");
    Tram::m_currentSpeed = currentSpeed;
    ENSURE(m_currentSpeed == currentSpeed, "m_currentspeed has to be set to currentSpeed.");
}

void Tram::updateLocation() {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_currentNode != NULL && m_currentNode->properlyInitialized(), "Current node cannot be NULL.");
    m_currentNode = m_currentNode->getNextNode();
}

int Tram::getVehicleNumber() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_vehicleNumber;
}

void Tram::setVehicleNumber(int vehicleNumber) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(vehicleNumber>=0,"Vehicle number must be a positive integer.");
    m_vehicleNumber = vehicleNumber;
    ENSURE(getVehicleNumber() == vehicleNumber,"m_vehicleNumber must be set to the vehicleNumber.");
}

bool Tram::properlyInitialized() const {
    return _initCheck == this;
}

