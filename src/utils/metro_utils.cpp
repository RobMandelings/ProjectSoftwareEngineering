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
#include "Direction.h"
#include "Track.h"
#include <fstream>
#include <sstream>
#include <map>


int metro_utils::stoi(const string& input) {
    int i;
    istringstream(input) >> i;
    return i;
}

string metro_utils::itos(const int input) {
    ostringstream ostring;
    ostring << input;
    return ostring.str();
}

string metro_utils::ctos(const char c) {
    std::stringstream ss;
    ss << c;

    return ss.str();
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
        if (currentTram->isOnTrack()) {
            outputFile << "\t\tCurrent location: " << currentTram->getCurrentTrack()->getSourcePlatform()->getStation()->getName() << " >> "
                       << currentTram->getCurrentTrack()->getDestinationPlatform()->getStation()->getName() << "\n";
            if (currentTram->getCurrentTrack()->getStopSignal() &&
                !currentTram->getCurrentTrack()->getWaitingTrams().empty()) {
                deque<Tram*> tramQueueCopy = currentTram->getCurrentTrack()->getWaitingTrams();
                bool inQueue = false;
                int index = -1;
                for (unsigned int i = 0; i < tramQueueCopy.size(); i++) {
                    if (tramQueueCopy.at(i) == currentTram) {
                        inQueue = true;
                        index = i;
                    }
                }
                if (inQueue) {
                    outputFile << "\t\tQueue Position: " << index + 1 << "\n";
                } else {
                    outputFile << "\t\tProgress: " << (int) (currentTram->getTrackProgress() * 100) << "%\n";
                }
            } else {
                outputFile << "\t\tProgress: " << (int) (currentTram->getTrackProgress() * 100) << "%\n";
            }
        } else {
            outputFile << "\t\tCurrent location: " << currentTram->getCurrentNode()->getStation()->getName() << "\n";
        }
    }

    outputFile.close();
}

void metro_utils::getGraphicalImpression(const char* inputfile, const char* outputFilename) {
    ifstream file(inputfile);
    string line;

    ofstream output;
    output.open(outputFilename);

    vector<pair<string, string> > lines;
    vector<pair<string, pair<string, string> > > trams;

    pair<string, string> currentTram;

    while (getline(file, line)) {

        if (line.find("\tLine", 0) == 0) {
            // Get line number and station order
            string lineNumber = line.substr(line.find(' ') + 1, line.find(':') - 1 - line.find(' '));
            string stationString = line.substr(line.find(':') + 2, line.rfind("Station") - line.find(':') - 7);

            // Remove the word "Station"
            while (stationString.find("Station") != string::npos) {
                stationString.replace(stationString.find("Station "), 8, "");
            }

            // Replace "-->" with "==="
            while (stationString.find(" --> ") != string::npos) {
                stationString.replace(stationString.find(" --> "), 5, "=======");
            }

            stationString += "===";
            stationString.insert(0, "===");

            lines.push_back(pair<string, string>(lineNumber, stationString));

        } else if (line.find("\tTram", 0) == 0) {
            string lineNumber = line.substr(line.find(' ') + 1, line.rfind(' ') - line.find(' ') - 1);
            string vehicleNumber = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);

            currentTram.first = lineNumber;
            currentTram.second = vehicleNumber;
        } else if (line.find("\t\tCurrent location:", 0) == 0) {
            string currentStation = line.substr(line.find(':') + 2, line.length() - 2);

            trams.push_back(pair<string, pair<string, string> >(currentStation, currentTram));
        }
    }

    vector<vector<string> > drawLines;

    for (unsigned int i = 0; i < lines.size(); i++) {
        vector<string> drawLine;
        drawLine.push_back("Line: " + lines.at(i).first);
        drawLine.push_back(lines.at(i).second);
        string tramPositions = "";

        // Add amount of spaces
        for (unsigned int n = 0; n < lines.at(i).second.length() + 4; n++) {
            tramPositions += " ";
        }

        for (unsigned int j = 0; j < trams.size(); j++) {
            if (trams.at(j).second.first == lines.at(i).first) {
                string pos = trams.at(j).first;
                if (pos.length() == 1) {
                    tramPositions.replace(lines.at(i).second.find(pos), 1, "T");
                } else {
                    if (tramPositions.at(tramPositions.find(pos.at(0)) + 3) == 'T') {
                        tramPositions.replace(tramPositions.find(pos.at(0)) + 5, 1,
                                              itos(stoi(ctos(tramPositions.at(tramPositions.find(pos.at(0)) + 5))) + 1));
                    } else {
                        int index = lines.at(i).second.find(pos.at(0)) + 3;
                        tramPositions.replace(index, 1, "T");
                        tramPositions.replace(index + 1, 1, ":");
                        tramPositions.replace(index + 2, 1, "1");
                    }
                }
            }
        }

        drawLine.push_back(tramPositions);
        drawLines.push_back(drawLine);
    }

    for (unsigned int i = 0; i < drawLines.size(); i++) {
        for (unsigned int j = 0; j < drawLines.at(i).size(); j++) {
            output << drawLines[i][j];
            output << "\n";
        }
        output << "\n";
    }

    output.close();
}