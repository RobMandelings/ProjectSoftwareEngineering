//
// Created by thibaultpoels on 27/02/2020.
//

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

const string &MetroNet::getName() const {
    return name;
}

void MetroNet::setName(const string& name) {
    MetroNet::name = name;
}

Tram * MetroNet::getTram(int line) const{
    for(unsigned int i = 0; i < MetroNet::trams.size();i++){
        if(MetroNet::trams[i]->getTramLine() == line){
            return MetroNet::trams[i];
        }
    }
    return NULL;
}


Station * MetroNet::getStation(const char* name) const{
    for(unsigned int i = 0; i < MetroNet::stations.size();i++){
        if(MetroNet::stations[i]->getName() == name){
            return MetroNet::stations[i];
        }
    }
    return NULL;
}

void MetroNet::addTram(Tram *tram) {
    MetroNet::trams.push_back(tram);
}

void MetroNet::addStation(Station *station) {
    MetroNet::stations.push_back(station);
}
