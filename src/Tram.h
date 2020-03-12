//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H

class TrackNode;

class Station;

class Tram {

private:

    int m_tramLine;
    int m_speed;
    int m_amountOfSeats;

    TrackNode* m_beginNode;
    TrackNode* m_currentNode;
public:

    const TrackNode* getBeginNode() const;

    const TrackNode* getCurrentNode() const;

    Tram(int line, int speed, int amountOfSeats, TrackNode* beginNode);

    int getTramLine() const;

    int getSpeed() const;

    int getAmountOfSeats() const;

    void setTramLine(int tramLine);

    void setSpeed(int speed);

    void setAmountOfSeats(int amountOfSeats);

    void updateLocation();

};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H