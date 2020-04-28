//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H

#include <string>
#include "Line.h"
#include "Direction.h"

class LineNode;

class Station;

class Track;

class Platform;

/**
 * Class containing settings and values of a Tram in the MetroNet
 */
class Tram {

private:

    /** The tram line this tram is following */
    Line* m_tramLine;

    /** The amount of seats in the tram */
    int m_amountOfSeats;

    /** The vehicle number of this tram */
    int m_vehicleNumber;

    /** The current speed of this tram in km/h */
    double m_currentSpeed;

    /** The current track progress of this tram (range 0 - 1) */
    double m_currentTrackProgress;

    /** How long this tram should still wait in this station */
    double m_currentWaitTime;

    /** The current direction of the tram */
    Direction m_currentDirection;

    /** The current platform this tram is on */
    Platform* m_currentPlatform;

    /** The current line node this tram is on (corresponding to a station) */
    LineNode* m_currentLineNode;

    /** The current track this tram is on */
    Track* m_currentTrack;

    Tram* _initCheck;

public:

    /** The length of the tram */
    const double LENGTH;

    /** The maximum speed this tram can go */
    const double MAX_SPEED;

    /** The type of the tram */
    const std::string TYPE;

public:

    /**
     * @brief Tram constructor
     * @param line: the line this tram should follow
     * @param beginPlatform: the beginPlatform of the line
     * @param maxSpeed: the maxSpeed of the tram
     * @param amountOfSeats: the maximum amount of seats in this tram
     * @param vehicleNumber: the vehicle number of the tram
     * @param length: the length of the tram
     * @param type: the type of the tram (Underground, Aboveground)
    \n ENSURE(m_tramLine>=0, "Line must be a positive number.");
    \n ENSURE(MAX_SPEED>=0, "Speed cannot be negative.");
    \n ENSURE(m_amountOfSeats>=0,"The amount of seats cannot be negative.");
    \n ENSURE(m_vehicleNumber>=0,"Vehicle number must be a positive number.");
    \n ENSURE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
    */
    Tram(Line* line, Platform* beginPlatform, double maxSpeed, int amountOfSeats, int vehicleNumber, double length, const std::string& type);

    /** @brief simple destructor */
    virtual ~Tram();

    /**
     * @brief checks if the tram is restricted to going underground or not
     * @return true if the tram can only go underground, false if not
     */
    virtual bool canOnlyGoUnderground() const { return false; };

    /**
     * @brief checks if the tram is on a track or not
     * @return true if the tram is currently on a track, false if not
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentTrack || m_currentPlatform, "The tram is not on a track and not on a platform");
     */
    bool isOnTrack() const;

    /**
     * @brief Simple getter
     * @return pointer to the current node in which the tram is located
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE( m_currentNode!=NULL && m_currentNode->properlyInitialized(),"The current node cannot be NULL.");
     */
    const LineNode* getCurrentNode() const;

    /**
     * @brief Simple getter
     * @return the tram's tram line (int)
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_tramLine>=0,"Line must be a positive number.");
     */
    Line* getTramLine() const;

    /**
     * @brief Simple getter
     * @return the tram's speed
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentSpeed>=0,"Speed cannot be negative.");
     */
    double getCurrentSpeed() const;

    /**
     * @brief simple getter
     * @return how long the tram should still wait at the station
    \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    double getCurrentWaitTime() const;

    /**
     * @brief Simple getter
     * @return the tram's amount of seats
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_amountOfSeats>=0,"Amount of seats cannot be negative.");
     */
    int getAmountOfSeats() const;

    /**
     * @brief Simple setter
     * @return set the tram's speed
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(currentSpeed>=0,"Amount of seats cannot be negative.");
     \n ENSURE(m_currentSpeed == currentSpeed, "m_currentSpeed has to be set to currentSpeed.");
     */
    void setCurrentSpeed(int currentSpeed);

    /**
     * @brief Simple getter
     * @return The vehicle number
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */

    int getVehicleNumber() const;

    /**
     * @brief Getter
     * @return Track
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */

    Track* getTrackForNextDestination();

    /**
     * @brief updates the location of the tram to the next station
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentNode != NULL && m_currentNode->properlyInitialized(), "Current node cannot be NULL.");
     */
    void update();

    /**
     * @brief updates the lineNode, depending on the current line node and the direction of the tram
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    void updateLineNode();

    /**
     * @brief Simple getter
     * @return LineNode
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    LineNode* getNextLineNode();

    /**
     * @brief Simple getter
     * @return Platform
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    Platform* getCurrentPlatform() const;

    /**
     * @brief Simple getter
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    double getTrackProgress() const;

    /**
     * @brief Simple setter
     * @param currentPlatform: new Platform
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    void putOnPlatform(Platform* currentPlatform);

    /**
     * @brief Simple getter
     * @return Track
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    Track* getCurrentTrack() const;

    /**
     * @brief Simple setter
     * @param currentTrack: new Track
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    void putOnTrack(Track* currentTrack);

    /**
     * @return the direction this tram should be on if it is on the current platform (depending on the Line)
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentPlatform != NULL, "The platform cannot be NULL");
     \n REQUIRE(m_currentPlatform == m_currentLineNode->getPlatform(TO) || m_currentPlatform == m_currentLineNode->getPlatform(FROM),
            "The current platform on the tram does not equal one of the 2 platforms of the current LineNode. This should not be possible");
     */
    Direction getCurrentPlatformDirection();

    /**
     * @brief simple getter
     * @return the current direction this tram is on
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */
    Direction getCurrentDirection() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};

std::ostream& operator<<(std::ostream& os, Tram& tram);

std::ostream& operator<<(std::ostream& os, Tram* tram);

#endif //PROJECTSOFTWAREENGINEERING_TRAM_H