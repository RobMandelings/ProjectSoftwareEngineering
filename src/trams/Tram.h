//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H

#include <string>

class LineNode;
class Station;

/**
 * Class containing settings and values of a Tram in the MetroNet
 */
class Tram {

private:

    int m_tramLine;

    /** The current speed of this tram in km/h */
    double m_currentSpeed;
    int m_amountOfSeats;

    LineNode* m_beginNode;
    LineNode* m_currentNode;

    Tram* _initCheck;

public:

    const double LENGTH;
    const double MAX_SPEED;
    const std::string TYPE;

public:

    virtual ~Tram();

    /**
     * @brief Simple getter
     * @return pointer to the tram line begin node
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
     */
    const LineNode* getBeginNode() const;

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
    \n ENSURE(m_beginNode!=NULL && m_beginNode->properlyInitialized(),"The begin node cannot be NULL.");
    \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
    */
    Tram(int line, LineNode* beginNode, double maxSpeed, int amountOfSeats, double length, const std::string& type);

    /**
     * @brief Simple getter
     * @return the tram's tram line (int)
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_tramLine>=0,"Line must be a positive number.");
     */
    int getTramLine() const;

    /**
     * @brief Simple getter
     * @return the tram's speed
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentSpeed>=0,"Speed cannot be negative.");
     */
    double getCurrentSpeed() const;

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
     * @brief updates the location of the tram to the next station
     \n REQUIRE(this->properlyInitialized(), "Tram must be initialized before its member variables are used.");
     \n REQUIRE(m_currentNode != NULL && m_currentNode->properlyInitialized(), "Current node cannot be NULL.");
     */
    void updateLocation();

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H