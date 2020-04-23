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

    Line* m_tramLine;

    int m_amountOfSeats;
    int m_vehicleNumber;

    /** The current speed of this tram in km/h */
    double m_currentSpeed;
    double m_currentTrackProgress;

    double m_currentWaitTime;

    Direction m_currentDirection;

    Platform* m_currentPlatform;
    LineNode* m_currentLineNode;

    Track* m_currentTrack;

    Tram* _initCheck;

public:

    const double LENGTH;
    const double MAX_SPEED;
    const std::string TYPE;

    virtual ~Tram();

    virtual bool canOnlyGoUnderground() const { return false; };

    bool isOnTrack() const;

    /**
     * @brief Simple getter
     * @return pointer to the current node in which the tram is located
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE( m_currentNode!=NULL && m_currentNode->properlyInitialized(),"The current node cannot be NULL.");
     */
    const LineNode* getCurrentNode() const;

    /**
     * @brief Tram constructor
    \n ENSURE(m_tramLine>=0, "Line must be a positive number.");
    \n ENSURE(MAX_SPEED>=0, "Speed cannot be negative.");
    \n ENSURE(m_amountOfSeats>=0,"The amount of seats cannot be negative.");
    \n ENSURE(m_vehicleNumber>=0,"Vehicle number must be a positive number.");
    \n ENSURE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
    */
    Tram(Line* line, Platform* beginPlatform, double maxSpeed, int amountOfSeats, int vehicleNumber, double length, const std::string& type);

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
    * @brief Simple setter
    * @return Set the Tram vehicle number
    \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
    \n REQUIRE(vehicleNumber>=0,"Vehicle number must be a positive integer.");
    \n ENSURE(getVehicleNumber() == vehicleNumber,"m_vehicleNumber must be set to the vehicleNumber.");
    */

    void setVehicleNumber(int vehicleNumber);

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

    Platform *getCurrentPlatform() const;

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

    void putOnPlatform(Platform *currentPlatform);

    /**
     * @brief Simple getter
     * @return Track
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */

    Track *getCurrentTrack() const;

    /**
     * @brief Simple setter
     * @param currentTrack: new Track
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     */

    void putOnTrack(Track* currentTrack);

    Direction getCurrentPlatformDirection();

    void updateLineNode();

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};

std::ostream& operator<<(std::ostream& os, Tram& tram);

std::ostream& operator<<(std::ostream& os, Tram* tram);


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H