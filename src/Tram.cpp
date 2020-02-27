//
// Created by rob on 27/02/2020.
//

#include "Tram.h"

Tram::Tram(int line, int speed, int amountOfSeats) : tramLine(line), speed(speed), amountOfSeats(amountOfSeats) {}

int Tram::getTramLine() const {
    return tramLine;
}

int Tram::getSpeed() const {
    return speed;
}

int Tram::getAmountOfSeats() const {
    return amountOfSeats;
}
