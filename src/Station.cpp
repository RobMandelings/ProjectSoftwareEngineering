//
// Created by jasper on 27/02/2020.
//

#include "Station.h"

const string& Station::getName() const {
    return m_name;
}

void Station::setName(const string& name) {
    Station::m_name = name;
}

Station* Station::getNext() const {
    return m_next;
}

void Station::setNext(Station* next) {
    Station::m_next = next;
}

Station* Station::getPrevious() const {
    return m_previous;
}

void Station::setPrevious(Station* previous) {
    Station::m_previous = previous;
}

int Station::getTrack() const {
    return m_track;
}

void Station::setTrack(int track) {
    Station::m_track = track;
}
