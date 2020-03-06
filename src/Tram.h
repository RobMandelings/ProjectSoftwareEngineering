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
public:
    TrackNode* getBeginNode() const;

    void setBeginNode(TrackNode* beginNode);

    Tram(int line, int speed, int amountOfSeats);

    Tram();

    int getTramLine() const;

    int getSpeed() const;

    int getAmountOfSeats() const;

    void setTramLine(int tramLine);

    void setSpeed(int speed);

    void setAmountOfSeats(int amountOfSeats);

};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H