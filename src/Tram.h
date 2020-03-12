//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H

class TrackNode;
class Station;

/**
 * Class containing settings and values of a Tram in the MetroNet
 */
class Tram {

private:

    int m_tramLine;
    int m_speed;
    int m_amountOfSeats;

    TrackNode* m_beginNode;
    TrackNode* m_currentNode;
public:

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

    Tram(int line, int speed, int amountOfSeats, TrackNode* beginNode);

    /**
     * @brief Simple getter
     * @return the tram's tram line (int)
     */
    int getTramLine() const;

    /**
     * @brief Simple getter
     * @return the tram's speed
     */
    int getSpeed() const;

    /**
     * @brief Simple getter
     * @return the tram's amount of seats
     */
    int getAmountOfSeats() const;

    /**
     * @brief Simple setter
     * @return set the tram's tram line
     */
    void setTramLine(int tramLine);

    /**
     * @brief Simple setter
     * @return set the tram's speed
     */
    void setSpeed(int speed);

    /**
     * @brief Simple setter
     * @return set the tram's amount of seats
     */
    void setAmountOfSeats(int amountOfSeats);

    /**
     * @brief updates the location of the tram to the next station
     */
    void updateLocation();

};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H