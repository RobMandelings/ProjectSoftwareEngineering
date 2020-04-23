//
// Created by thibaultpoels on 27/02/2020.
//

#include <fstream>
#include <DesignByContract.h>
#include "lines/LineNode.h"
#include "metro_utils.h"
#include "../MetroNet.h"
#include "Station.h"
#include "../trams/Tram.h"
#include "enums.h"
#include "Track.h"
#include <fstream>
#include <sstream>
#include <map>


int metro_utils::stoi(const string& input) {
    int i;
    istringstream(input) >> i;
    return i;
}

double metro_utils::stod(const string& input) {
    double i;
    istringstream(input) >> i;
    return i;
}

void metro_utils::printMetroNet(MetroNet* metroNet, const char* outputFilename) {

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
    vector<Line*> lines = metroNet->getLines();
    vector<Tram*> trams = metroNet->getTrams();

    outputFile << "MetroNet: " << metroNet->getName() << "\n";
    outputFile << "Stations:" << "\n";
    for (vector<Station*>::iterator stationIt = stations.begin(); stationIt != stations.end(); stationIt++) {
        outputFile << "\t(" << (*stationIt)->getType() << ") station '" << (*stationIt)->getName() << "'" << "\n";
    }

    outputFile << "Lines:" << "\n";
    for (vector<Line*>::iterator lineIt = lines.begin(); lineIt != lines.end(); lineIt++) {
        outputFile << "\tLine " << (*lineIt)->getLineNumber() << ": " << (*lineIt)->getAsString() << "\n";
    }

    outputFile << "Trams:" << "\n";
    for (vector<Tram*>::iterator tramIt = trams.begin(); tramIt != trams.end(); tramIt++) {
        Tram* currentTram = *tramIt;
        outputFile << "\t" << "Tram " << currentTram->getTramLine()->getLineNumber() << " (" << currentTram->getVehicleNumber() << ")" << ":" << "\n";
        outputFile << "\t\tType: " << currentTram->TYPE << "\n";
        outputFile << "\t\tMax Speed: " << currentTram->MAX_SPEED << "\n";
        outputFile << "\t\tCurrent speed: " << currentTram->getCurrentSpeed() << "\n";
        outputFile << "\t\tAmount of Seats: " << currentTram->getAmountOfSeats() << "\n";
        outputFile << "\t\tLength: " << currentTram->LENGTH << "\n";
        if(currentTram->isOnTrack()){
            outputFile << "\t\tCurrent location: " << currentTram->getCurrentTrack()->getSourcePlatform()->getStation()->getName() << " >> " << currentTram->getCurrentTrack()->getDestinationPlatform()->getStation()->getName() << "\n";
            if(currentTram->getCurrentTrack()->getStopSignal() &&
               !currentTram->getCurrentTrack()->getWaitingTrams().empty()){
                deque<Tram*> tramQueueCopy = currentTram->getCurrentTrack()->getWaitingTrams();
                bool inQueue = false;
                int index = -1;
                for(unsigned int i = 0;i<tramQueueCopy.size();i++){
                    if(tramQueueCopy.at(i)==currentTram){
                        inQueue = true;
                        index = i;
                    }
                }
                if(inQueue){
                    outputFile << "\t\tQueue Position: " << index + 1 << "\n";
                } else {
                    outputFile << "\t\tProgress: " << (int) (currentTram->getTrackProgress()*100) << "%\n";
                }
            } else {
                outputFile << "\t\tProgress: " << (int) (currentTram->getTrackProgress()*100) << "%\n";
            }
        } else {
            outputFile << "\t\tCurrent location: " << currentTram->getCurrentNode()->getStation()->getName() << "\n";
        }
    }

    outputFile.close();
}

void metro_utils::getGraphicalImpression(const char* inputfile, const char* outputFilename){
    ifstream file(inputfile);
    string line;

    ofstream output;
    output.open (outputFilename);

    vector<pair<string,string> > lines;
    vector<pair<string,pair<string,string> > > trams;

    while(getline(file, line)){
        pair<string,string> currentTram;

        if(line.find("\tLine", 0) == 0){
            // Get line number and station order
            string lineNumber = line.substr(line.find(' ') + 1, line.find(':') - 1 - line.find(' '));
            string stationString = line.substr(line.find(':') + 2, line.rfind("Station") - line.find(':') - 7);

            // Remove the word "Station"
            while(stationString.find("Station") != string::npos){
                stationString.replace(stationString.find("Station "),8,"");
            }

            // Replace "-->" with "==="
            while(stationString.find("-->") != string::npos){
                stationString.replace(stationString.find("-->"),3,"====");
            }

            lines.push_back(pair<string,string>(lineNumber,stationString));

        } else if(line.find("\tTram", 0) == 0){
            string lineNumber = line.substr(line.find(' ')+1, line.rfind(' ') - line.find(' ')-1);

        }
    }



    output.close();
}