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
    Station* m_beginStation;
    TrackNode* m_beginNode;
public:
    Station* getBeginStation() const;

    void setBeginStation(Station* beginStation);

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