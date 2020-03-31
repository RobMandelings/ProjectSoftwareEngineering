//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H

#include <string>

class TrackNode;
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

    TrackNode* m_beginNode;
    TrackNode* m_currentNode;

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
    const TrackNode* getBeginNode() const;

    /**
     * @brief Simple getter
     * @return pointer to the current node in which the tram is located
     */
    const TrackNode* getCurrentNode() const;

    Tram(int line, TrackNode* beginNode, double maxSpeed, int amountOfSeats, double length, const std::string& type);

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

};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H