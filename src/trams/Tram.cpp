//
// Created by rob on 27/02/2020.
//
#include <cmath>

#include "Tram.h"
#include "LineNode.h"
#include "Track.h"
#include "Platform.h"

Tram::Tram(Line* line, Platform* beginPlatform, double maxSpeed, int amountOfSeats, int vehicleNumber, double length, const std::string& type) :
        m_tramLine(line),
        m_amountOfSeats(amountOfSeats),
        m_vehicleNumber(vehicleNumber),
        m_currentSpeed(maxSpeed),
        m_currentPlatform(beginPlatform),
        m_currentLineNode(line->getNodeForStation(beginPlatform->getStation())),
        m_currentTrack(NULL),
        LENGTH(length),
        MAX_SPEED(maxSpeed),
        TYPE(type) {
    Tram::_initCheck = this;
    ENSURE(line->getNodeForStation(beginPlatform->getStation()) != NULL, "Tram constructor: the beginPlatform is not on the line (traject) of the tram");
    ENSURE(m_tramLine != NULL, "Line must be a positive number.");
    ENSURE(MAX_SPEED >= 0, "Speed cannot be negative.");
    ENSURE(m_amountOfSeats >= 0, "The amount of seats cannot be negative.");
    ENSURE(m_vehicleNumber >= 0, "Vehicle number must be a positive number.");
    ENSURE(m_currentPlatform != NULL && m_currentPlatform->properlyInitialized(), "The begin node cannot be NULL.");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Tram::~Tram() {}

const LineNode* Tram::getCurrentNode() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentLineNode;
}

Line* Tram::getTramLine() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_tramLine != NULL, "The tram line should not be a nullptr");
    return m_tramLine;
}

double Tram::getCurrentSpeed() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_currentSpeed >= 0, "Speed cannot be negative.");
    return m_currentSpeed;
}

int Tram::getAmountOfSeats() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(m_amountOfSeats >= 0, "Amount of seats cannot be negative.");
    return m_amountOfSeats;
}

void Tram::setCurrentSpeed(int currentSpeed) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(currentSpeed >= 0, "Amount of seats cannot be negative.");
    Tram::m_currentSpeed = currentSpeed;
    ENSURE(m_currentSpeed == currentSpeed, "m_currentspeed has to be set to currentSpeed.");
}

void Tram::update(long timeSinceLastUpdate) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    m_currentLineNode = m_currentLineNode->getNextNode();

    // If the tram is currently in a station
    if (!isOnTrack()) {

        bool waitTimeZero = true;
        if (m_currentWaitTime > 0) {

            m_currentWaitTime -= (double) timeSinceLastUpdate;

            // If the current wait time is now smaller than or equal to 0
            if (m_currentWaitTime < 0) {
                // Tijd dat er te veel is afgegaan van de currentWait time zetten in timeSinceLastUpdate
                timeSinceLastUpdate = (long) std::abs(m_currentWaitTime);
                m_currentWaitTime = 0;
            } else {
                waitTimeZero = false;
            }
        }

        // If the condition is true, do other checks to see whether or not the tram should leave its station
        if (waitTimeZero) {
            // TODO Collision prevention: check if no other trams are currently in the next station

        }

    } else {
        // Verander positie
    }
}

int Tram::getVehicleNumber() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_vehicleNumber;
}

void Tram::setVehicleNumber(int vehicleNumber) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(vehicleNumber >= 0, "Vehicle number must be a positive integer.");
    m_vehicleNumber = vehicleNumber;
    ENSURE(getVehicleNumber() == vehicleNumber, "m_vehicleNumber must be set to the vehicleNumber.");
}

Track* Tram::getTrackForNextDestination() {
    Track* trackForNextDestination = NULL;
    // If it is not in a station but already on a track, just return that track
    if (!m_currentPlatform) {
        REQUIRE(m_currentTrack, " if the tram is not on a platform, the tram should be on a track!");
        return m_currentTrack;
    } else {
        REQUIRE(!m_currentTrack, " if the tram is on a platform, the tram should not be on a track!");
        Station* nextStation = m_currentLineNode->getNextStation();
        for (std::vector<Track*>::iterator trackIt = m_currentPlatform->getOutgoingTracks().begin(); trackIt < m_currentPlatform->getOutgoingTracks().end(); trackIt++) {
            // TODO if multiple tracks can bring the same tram to the same location, choose the current best track to put the tram on
            // (probably defined by the amount of trams on a specific track)
            if ((*trackIt)->getDestinationPlatform()->getStation() == nextStation) {
                trackForNextDestination = *trackIt;
            }
        }
    }

//    TODO ENSURE(trackForNextDestination != NULL, " the track for the next destination does not exists, this should not be possible.");
    return trackForNextDestination;
}

bool Tram::properlyInitialized() const {
    return _initCheck == this;
}

bool Tram::isOnTrack() const {
    return m_currentTrack != NULL;
}