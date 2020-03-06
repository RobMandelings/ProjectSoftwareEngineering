//
// Created by thibaultpoels on 27/02/2020.
//

#include "../TrackNode.h"
#include "metroUtils.h"
#include "../MetroNet.h"
#include "../Station.h"

int metroUtils::stoi(const string& input) {
    int i;
    istringstream(input) >> i;
    return i;
}

void metroUtils::printMetroNet(MetroNet* metroNet) {

    if (metroNet == NULL) {
        std::cout << "MetroNet could not be printed to the console: given MetroNet is NULL" << std::endl;
        return;
    }

    std::cout << "MetroNet: " << metroNet->getName() << std::endl;
    std::cout << "Stations: " << std::endl;
    vector<Station*> stations = metroNet->getStations();
    for (vector<Station*>::iterator stationIt = stations.begin(); stationIt != stations.end(); stationIt++) {

    }
}

std::ostream& operator<<(std::ostream& os, Station* station) {
    os << station->getName();
    return os;
}