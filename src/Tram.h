//
// Created by rob on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TRAM_H
#define PROJECTSOFTWAREENGINEERING_TRAM_H


class Tram {

private:

    int tramLine;
    int speed;
    int amountOfSeats;

public:

    Tram(int line, int speed, int amountOfSeats);

    int getTramLine() const;

    int getSpeed() const;

    int getAmountOfSeats() const;

};


#endif //PROJECTSOFTWAREENGINEERING_TRAM_H
