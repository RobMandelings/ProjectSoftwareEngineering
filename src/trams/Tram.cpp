//
// Created by rob on 27/02/2020.
//
#include <cmath>
#include <utils/constants.h>

#include "Tram.h"
#include "LineNode.h"
#include "Track.h"
#include "Platform.h"
#include "Station.h"
#include "Timer.h"
#include "SpeedSignal.h"
#include "StopSignal.h"

Tram::Tram(Line* line, Platform* beginPlatform, double maxSpeed, int amountOfSeats, int vehicleNumber, double length, const std::string& type) :
        m_tramLine(line),
        m_amountOfSeats(amountOfSeats),
        m_vehicleNumber(vehicleNumber),
        m_currentSpeed(maxSpeed),
        m_currentTrackProgress(0),
        m_currentWaitTime(constants::TRAM_WAIT_TIME),
        m_currentDirection(TO),
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
    ENSURE(m_currentDirection != FROM, "Direction has to be forward when initializing a tram.");
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

double Tram::getCurrentWaitTime() const {
    return m_currentWaitTime;
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

void Tram::update(std::ofstream& outfile) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");

    // If the tram is currently in a station
    if (!isOnTrack()) {
        REQUIRE(this->getTrackForNextDestination(), "The track for the next destination is not found. This should not be possible");
        m_currentWaitTime -= (double) Timer::get().getTimePassedMillis() / 1000;
        Track* trackForNextDestination = this->getTrackForNextDestination();

        if (m_currentWaitTime <= 0) {
            m_currentWaitTime = 0;
            if (trackForNextDestination->getStopSignal()) {
                if (!trackForNextDestination->tramCapacityReached()) {
                    // TODO if not debug print as well, also add correct time of day
                    outfile << "Putting tram nr " << getVehicleNumber() << " on the next track, destination: "
                            << trackForNextDestination->getDestinationPlatform()->getStation()->getName() << std::endl;

                    putOnTrack(trackForNextDestination);
                }
            } else {
                if (trackForNextDestination->getDestinationPlatform()->canReceiveNewIncomingTram()) {
                    // TODO if not debug print as well, also add correct time of day
                    outfile << "Another tram is going to be received at platform " << trackForNextDestination->getDestinationPlatform()->getNumber() << ", station "
                            << trackForNextDestination->getDestinationPlatform()->getStation()->getName() << std::endl;
                    trackForNextDestination->getDestinationPlatform()->receiveNewIncomingTram();
                }
            }
        }
    } else {
        if (m_currentTrackProgress < 1) {
            m_currentTrackProgress += ((double) Timer::get().getTimePassedMillis() / 1000) / (7200 / getCurrentSpeed());
            if (m_currentTrackProgress >= 1) {
                if (m_currentTrack->getStopSignal()) {
                    outfile << "Tram nr " << getVehicleNumber() << " has completed a track journey to: "
                            << this->getTrackForNextDestination()->getDestinationPlatform()->getStation()->getName()
                            << ", adding it to the waiting list" << std::endl;
                    m_currentTrack->addWaitingTram(this);
                    m_currentTrackProgress = 1;
                    // Should it be done like this?
                    if (m_currentTrack->getDestinationPlatform()->canReceiveNewIncomingTram()) {
                        // TODO if not debug print as well, also add correct time of day
                        outfile << "Another tram is going to be received at platform " << m_currentTrack->getDestinationPlatform()->getNumber() << ", station "
                                << m_currentTrack->getDestinationPlatform()->getStation()->getName() << std::endl;
                        m_currentTrack->getDestinationPlatform()->receiveNewIncomingTram();
                    }
                } else {
                    outfile << "Tram nr " << getVehicleNumber() << " has arrived in: "
                            << this->getTrackForNextDestination()->getDestinationPlatform()->getStation()->getName()
                            << "" << std::endl;
                    m_currentTrack->getDestinationPlatform()->setCurrentTram(this);
                    this->putOnPlatform(m_currentTrack->getDestinationPlatform());
                }
            }
        }
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
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    Track* trackForNextDestination = NULL;
    // If it is not in a station but already on a track, just return that track
    if (!m_currentPlatform) {
        REQUIRE(m_currentTrack, "If the tram is not on a platform, the tram should be on a track!");
        return m_currentTrack;
    } else {
        REQUIRE(!m_currentTrack, "If the tram is on a platform, the tram should not be on a track!");
        Platform* nextPlatform = this->getNextLineNode()->getPlatform(m_currentDirection);
        for (std::vector<Track*>::iterator trackIt = m_currentPlatform->getOutgoingTracks().begin(); trackIt < m_currentPlatform->getOutgoingTracks().end(); trackIt++) {
            if ((*trackIt)->getDestinationPlatform() == nextPlatform) {
                trackForNextDestination = (*trackIt);
            }
        }
    }

    ENSURE(trackForNextDestination != NULL, "The track for the next destination does not exists, this should not be possible.");
    return trackForNextDestination;
}

bool Tram::properlyInitialized() const {
    return _initCheck == this;
}

bool Tram::isOnTrack() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentTrack != NULL;
}

LineNode* Tram::getNextLineNode() {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    if (m_currentDirection == TO) {
        return m_currentLineNode->getNextNode();
    } else {
        return m_currentLineNode->getPreviousNode();
    }
}

void Tram::updateLineNode() {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    m_currentLineNode = getNextLineNode();

    // Reached the end of the 'heen' journey
    if (m_currentDirection == TO && m_currentLineNode == m_tramLine->getFirstNode()->getPreviousNode()) {
        m_currentDirection = FROM;
        // Reached the end of the 'terug' journey
    } else if (m_currentDirection == FROM && m_currentLineNode == m_tramLine->getFirstNode()) {
        m_currentDirection = TO;
    }
}

Platform* Tram::getCurrentPlatform() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentPlatform;
}

Track* Tram::getCurrentTrack() const {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    return m_currentTrack;
}

void Tram::putOnPlatform(Platform* currentPlatform) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(currentPlatform, "The platform given cannot be NULL");
    REQUIRE(currentPlatform != m_currentPlatform, "The platform to put the tram on is the same as the current platform");
    m_currentPlatform = currentPlatform;

    m_currentTrack->deleteTram();
    m_currentTrack = NULL;

    m_currentSpeed = 0;
    m_currentWaitTime = m_currentPlatform->getStation()->getType() == ABOVE_GROUND && canOnlyGoUnderground() ? 1 : constants::TRAM_WAIT_TIME;
    this->updateLineNode();
}

void Tram::putOnTrack(Track* currentTrack) {
    REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    REQUIRE(currentTrack, "The track given cannot be NULL");
    REQUIRE(currentTrack != m_currentTrack, "The track to put the tram on is the same as the current track");
    m_currentTrack = currentTrack;
    m_currentTrack->increaseAmountOfTrams();
    m_currentTrackProgress = 0;

    Platform* oldPlatform = m_currentPlatform;
    m_currentPlatform = NULL;

    m_currentSpeed = m_currentTrack->getSpeedSignal() ? m_currentTrack->getSpeedSignal()->getSpeed() : MAX_SPEED;

    if (oldPlatform->canReceiveNewIncomingTram()) {
        oldPlatform->receiveNewIncomingTram();
    }
    ENSURE(m_currentTrack == currentTrack, "The tram is not on placed on the track given!");
}
