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
     */
    const LineNode* getBeginNode() const;

    /**
     * @brief Simple getter
     * @return pointer to the current node in which the tram is located
     */
    const LineNode* getCurrentNode() const;

    Tram(int line, LineNode* beginNode, double maxSpeed, int amountOfSeats, double length, const std::string& type);

    /**
     * @brief Simple getter
     * @return the tram's tram line (int)
     */
    int getTramLine() const;

    /**
     * @brief Simple getter
     * @return the tram's speed
     */
    double getCurrentSpeed() const;

    /**
     * @brief Simple getter
     * @return the tram's amount of seats
     */
    int getAmountOfSeats() const;

    /**
     * @brief Simple setter
     * @return set the tram's speed
     */
    void setCurrentSpeed(int currentSpeed);

    /**
     * @brief updates the location of the tram to the next station
     */
    void updateLocation();

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H