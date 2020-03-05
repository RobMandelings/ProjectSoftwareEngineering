//
// Created by thibaultpoels on 27/02/2020.
//

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

const string &MetroNet::getName() const {
    return m_name;
}

void MetroNet::setName(const string& name) {
    MetroNet::m_name = name;
}

Tram * MetroNet::getTram(int line) const{
    for(unsigned int i = 0; i < MetroNet::m_trams.size(); i++){
        if(MetroNet::m_trams[i]->getTramLine() == line){
            return MetroNet::m_trams[i];
        }
    }
    return NULL;
}


Station * MetroNet::getStation(const char* name) const{
    for(unsigned int i = 0; i < MetroNet::m_stations.size(); i++){
        if(MetroNet::m_stations[i]->getName() == name){
            return MetroNet::m_stations[i];
        }
    }
    return NULL;
}

void MetroNet::addTram(Tram *tram) {
    MetroNet::m_trams.push_back(tram);
}

void MetroNet::addStation(Station *station) {
    MetroNet::m_stations.push_back(station);
}

void MetroNet::addTrack(Track* track) {
    //TODO empty method stub
}