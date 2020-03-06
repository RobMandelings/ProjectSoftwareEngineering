//
// Created by thibaultpoels on 27/02/2020.
//

#include <fstream>
#include "../TrackNode.h"
#include "metroUtils.h"
#include "../MetroNet.h"
#include "../Station.h"
#include "../Tram.h"

int metroUtils::stoi(const string& input) {
    int i;
    istringstream(input) >> i;
    return i;
}

void metroUtils::printMetroNet(MetroNet* metroNet, const char* outputFilename) {

    ofstream outputFile;
    outputFile.open(outputFilename);

    if (outputFile.fail()) {
        std::cerr << "Metronet could not be printed to the console: the file with name '" << outputFilename << "' wasn't found" << std::endl;
    }

    if (metroNet == NULL) {
        std::cerr << "MetroNet could not be printed to the console: given MetroNet is NULL" << std::endl;
        return;
    }

    vector<Station*> stations = metroNet->getStations();
    vector<Track*> tracks = metroNet->getTracks();
    vector<Tram*> trams = metroNet->getTrams();

    outputFile << "MetroNet: " << metroNet->getName() << std::endl;
    outputFile << "Stations: " << std::endl;
    for (vector<Station*>::iterator stationIt = stations.begin(); stationIt != stations.end(); stationIt++) {
        outputFile << "\tStation '" << (*stationIt)->getName() << "'" << endl;
    }

    outputFile << "Tracks:" << endl;
    for (vector<Track*>::iterator trackIt = tracks.begin(); trackIt != tracks.end(); trackIt++) {
        outputFile << "\tTrack " << (*trackIt)->getLine() << ": " << (*trackIt)->getAsString() << std::endl;
    }

    outputFile << "Trams:" << endl;
    for (vector<Tram*>::iterator tramIt = trams.begin(); tramIt != trams.end(); tramIt++) {
        Tram* currentTram = *tramIt;
        outputFile << "\tTram " << currentTram->getTramLine() << ": " << endl;
        outputFile << "\t\tSpeed: " << currentTram->getSpeed() << endl;
        outputFile << "\t\tAmount of Seats: " << currentTram->getAmountOfSeats() << endl;
    }

    outputFile.close();
}