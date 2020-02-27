//
// Created by jasper on 27/02/2020.
//

#include "Station.h"

const string& Station::getName() const {
    return name;
}

void Station::setName(const string& name) {
    Station::name = name;
}

Station* Station::getNext() const {
    return next;
}

void Station::setNext(Station* next) {
    Station::next = next;
}

Station* Station::getPrevious() const {
    return previous;
}

void Station::setPrevious(Station* previous) {
    Station::previous = previous;
}

int Station::getTrack() const {
    return track;
}

void Station::setTrack(int track) {
    Station::track = track;
}
