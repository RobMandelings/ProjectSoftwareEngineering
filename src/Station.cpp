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

Track* Station::getTrack(int number) const {
    for(vector<Track*>::iterator it = m_tracks.begin(); it != m_tracks.end(); ++it){
        if(it->getIndex() == number){
            return it;
        }
    }

    return NULL;
}

void Station::addTrack(Track* track) {
    m_tracks.push_back(track);
}
