//
// Created by rob on 27/02/2020.
//

#include "Tram.h"

Tram::Tram(int line, int speed, int amountOfSeats) : m_tramLine(line), m_speed(speed), m_amountOfSeats(amountOfSeats) {}

int Tram::getTramLine() const {
    return m_tramLine;
}

int Tram::getSpeed() const {
    return m_speed;
}

int Tram::getAmountOfSeats() const {
    return m_amountOfSeats;
}

void Tram::setTramLine(int tramLine) {
    Tram::m_tramLine = tramLine;
}

void Tram::setSpeed(int speed) {
    Tram::m_speed = speed;
}

void Tram::setAmountOfSeats(int amountOfSeats) {
    Tram::m_amountOfSeats = amountOfSeats;
}

Tram::Tram() {}

TrackNode* Tram::getBeginNode() const {
    return m_beginNode;
}

void Tram::setBeginNode(TrackNode* beginNode) {
    Tram::m_beginNode = beginNode;
}
