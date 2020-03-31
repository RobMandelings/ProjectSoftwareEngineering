//
// Created by rob on 27/02/2020.
//

#include "Tram.h"
#include "TrackNode.h"

Tram::Tram(int line, TrackNode* beginNode, double maxSpeed, int amountOfSeats, double length, const std::string& type) :
        m_tramLine(line),
        m_currentSpeed(maxSpeed),
        m_amountOfSeats(amountOfSeats),
        m_beginNode(beginNode),
        m_currentNode(beginNode),
        LENGTH(length),
        MAX_SPEED(maxSpeed),
        TYPE(type) {}

Tram::~Tram() {}

const TrackNode* Tram::getBeginNode() const {
    return m_beginNode;
}

const TrackNode* Tram::getCurrentNode() const {
    return m_currentNode;
}

int Tram::getTramLine() const {
    return m_tramLine;
}

double Tram::getCurrentSpeed() const {
    return m_currentSpeed;
}

int Tram::getAmountOfSeats() const {
    return m_amountOfSeats;
}

void Tram::setCurrentSpeed(int currentSpeed) {
    Tram::m_currentSpeed = currentSpeed;
}

void Tram::updateLocation() {
    m_currentNode = m_currentNode->getNextNode();
}