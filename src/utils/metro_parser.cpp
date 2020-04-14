//
// Created by Rob Mandelings on 6/03/2020.
//

#include "metro_parser.h"
#include "../MetroNet.h"
#include "../trams/Tram.h"
#include "lines/Line.h"
#include "lines/LineNode.h"
#include "metro_utils.h"
#include "DesignByContract.h"
#include "Albatros.h"
#include "PCC.h"
#include "Station.h"
#include "MetroStation.h"
#include "TramStop.h"
#include "Platform.h"
#include "Track.h"

namespace metro_parser {

    namespace {

        Platform* parsePlatform(TiXmlElement* platformElement, bool debug) {
            int platformNumber = -1;
            for (TiXmlElement* currentPerronChildElement = platformElement->FirstChildElement();
                 currentPerronChildElement != NULL; currentPerronChildElement = currentPerronChildElement->NextSiblingElement()) {
                if (!strcmp(currentPerronChildElement->Value(), "nummer")) {
                    platformNumber = metro_utils::stoi(currentPerronChildElement->GetText());
                }
            }
            if (platformNumber < 0) {
                if (!debug) std::cerr << "The platform number cannot be negative" << std::endl;
                throw MetroNetParseException();
            } else {
                return new Platform(platformNumber);
            }
        }

        void parseTrack(MetroNet* metroNet, TiXmlElement* trackElement, bool debug) {

            //TODO mirror tracks?
            std::vector<Platform*> platformNodes;

            for (TiXmlElement* stationElement = trackElement->FirstChildElement();
                 stationElement != NULL; stationElement = stationElement->NextSiblingElement()) {
                if (!strcmp(stationElement->Value(), "station")) {
                    Station* station = NULL;
                    std::string stationName;
                    int platformNumber = -1;

                    for (TiXmlElement* stationChildElement = stationElement->FirstChildElement();
                         stationChildElement != NULL; stationChildElement = stationChildElement->NextSiblingElement()) {
                        if (!strcmp(stationChildElement->Value(), "naam")) {
                            station = metroNet->getStation(stationChildElement->GetText());
                            stationName = stationChildElement->GetText();
                        } else if (!strcmp(stationChildElement->Value(), "perron")) {
                            platformNumber = metro_utils::stoi(stationChildElement->GetText());
                        } else {
                            if (!debug) std::cerr << " unrecognized element '" << stationChildElement->Value() << "' within station" << std::endl;
                            throw MetroNetParseException();
                        }
                    }
                    if (station) {
                        Platform* platform = NULL;
                        if (station->getType() == UNDERGROUND) {
                            MetroStation* metroStation = (MetroStation*) station;
                            platform = metroStation->getPlatform(platformNumber);
                        } else {
                            TramStop* tramStop = (TramStop*) station;
                            if (tramStop->getPlatform()->getNumber() == platformNumber) {
                                platform = tramStop->getPlatform();
                            }
                        }

                        if (platform) {
                            platformNodes.push_back(platform);
                        } else {
                            if (!debug) std::cerr << "platform '" << platformNumber << "' was not found within station" << std::endl;
                            throw MetroNetParseException();
                        }
                    } else {
                        if (!debug) std::cerr << "station '" << stationName << "' was not found for track" << std::endl;
                        throw MetroNetParseException();
                    }
                } else {
                    if (!debug) std::cerr << " the node within track '" << stationElement->Value() << "' is not recognized as station" << std::endl;
                    throw MetroNetParseException();
                }
            }

            if (platformNodes.size() == 2) {
                Platform* sourcePlatform = platformNodes.at(0);
                Platform* destinationPlatform = platformNodes.at(1);
                if (sourcePlatform != destinationPlatform) {
                    if (!metroNet->trackExists(sourcePlatform, destinationPlatform)) {
                        Track* track = new Track(sourcePlatform, destinationPlatform);
                        sourcePlatform->addOutgoingTrack(track);
                        destinationPlatform->addIncomingTrack(track);
                        metroNet->addTrack(track);
                    } else {
                        if (!debug)
                            std::cerr << "track with source platform 'station " << sourcePlatform->getStation()->getName() << ", number " << sourcePlatform->getNumber() << "'"
                                      << " and destination platform 'station " << destinationPlatform->getStation()->getName() << ", number " << destinationPlatform->getNumber()
                                      << "' already exists in the metronet" << std::endl;
                        throw MetroNetParseException();
                    }
                } else {
                    if (!debug)
                        std::cerr << "The destination of the track is equal to the source (station: " << sourcePlatform->getStation()->getName() << ", number: "
                                  << sourcePlatform->getNumber() << ")" << std::endl;
                    throw MetroNetParseException();
                }
            } else {
                if (!debug) std::cerr << "The amount of platforms for a track should be equal to 2. Given: " << platformNodes.size() << std::endl;
                throw MetroNetParseException();
            }
        }

        void parseStation(MetroNet* metroNet, TiXmlElement* stationElement, bool debug) {

            string stationName;
            std::string stationType;
            std::vector<Platform*> platforms;

            for (TiXmlElement* currentChildElement = stationElement->FirstChildElement(); currentChildElement != NULL;
                 currentChildElement = currentChildElement->NextSiblingElement()) {
                string childElementName = currentChildElement->Value();
                if (childElementName == "naam") {
                    stationName = currentChildElement->GetText();
                } else if (childElementName == "type") {
                    stationType = currentChildElement->GetText();
                } else if (childElementName == "perron") {
                    platforms.push_back(parsePlatform(currentChildElement, debug));
                }
            }

            if (platforms.empty()) {
                if (!debug) std::cerr << "There are no platforms found for the current station " << stationName << std::endl;
                throw MetroNetParseException();
            }
            Station* currentStation = NULL;
            if (stationType == "MetroStation") {
                MetroStation* metroStation = new MetroStation();
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
                    if (metroStation->getPlatform((*it)->getNumber()) == NULL) {
                        metroStation->addPlatform(*it);
                    } else {
                        if (!debug) std::cerr << "The platform with number " << (*it)->getNumber() << " already exists in the metrostation" << std::endl;
                        throw MetroNetParseException();
                    }
                }
                currentStation = metroStation;
            } else if (stationType == "TramStop") {
                if (platforms.size() > 1) {
                    if (!debug) std::cerr << "A tram stap can only have 1 platform. Given: " << platforms.size() << std::endl;
                    throw MetroNetParseException();
                } else {
                    currentStation = new TramStop(platforms.at(0));
                }
            } else {
                if (!debug) std::cerr << "The type of the station wasn't recognized" << stationType << std::endl;
                throw MetroNetParseException();
            }

            // The station of the platform is set to the currentStation
            for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); it++) {
                (*it)->setStation(currentStation);
            }
            currentStation->setName(stationName);
            metroNet->addStation(currentStation);
        }

        void parseLine(MetroNet* metroNet, TiXmlElement* lineElement, bool debug) {
            Line* currentLine = new Line();
            int lineIndex = metro_utils::stoi(lineElement->Attribute("index"));
            currentLine->setLineNumber(lineIndex);
            for (TiXmlElement* elem = lineElement->FirstChildElement();
                 elem != NULL; elem = elem->NextSiblingElement()) {
                if (!strcmp(elem->Value(), "LIJNNODE")) {
                    Station* station = metroNet->getStation(elem->Attribute("station"));
                    if (station) {
                        station->addLine(currentLine);
                        LineNode* node = new LineNode(lineIndex, metroNet->getStation(elem->Attribute("station")));
                        currentLine->insertNode(node);
                    } else {
                        if (!debug)
                            cerr << "MetroParser: Station with name " << elem->Attribute("station")
                                 << " wasn't found" << endl;
                        throw MetroNetParseException();
                    }
                }
            }
            metroNet->addLine(currentLine);
        }

        void parseTram(MetroNet* metroNet, TiXmlElement* tramElement, bool debug) {

            Line* line = NULL;
            Platform* beginPlatform = NULL;
            std::string type = "Tram";

            // Only used if the type is tram
            int amountOfSeats = -1;
            int vechicleNumber = -1;
            double speed = -1;
            double length = -1;

            for (TiXmlElement* tramChildElement = tramElement->FirstChildElement(); tramChildElement != NULL;
                 tramChildElement = tramChildElement->NextSiblingElement()) {
                string elementName = tramChildElement->Value();
                if (elementName == "lijn") {
                    int lineIndex = metro_utils::stoi(tramChildElement->GetText());
                    if (lineIndex > 0) {
                        line = metroNet->getLine(lineIndex);
                    }
                } else if (elementName == "type") {
                    type = tramChildElement->GetText();
                } else if (elementName == "length") {
                    length = metro_utils::stod(tramChildElement->GetText());
                } else if (elementName == "voertuigNr") {
                    vechicleNumber = metro_utils::stoi(tramChildElement->GetText());
                }
                //TODO what to do if the type is not a default tram but PCC for example? 'zitplaatsen' should not be used in this case
                if (elementName == "zitplaatsen") {
                    amountOfSeats = metro_utils::stoi(tramChildElement->GetText());
                } else if (elementName == "snelheid") {
                    speed = metro_utils::stod(tramChildElement->GetText());
                } else if (elementName == "beginStation") {
                    Station* station = NULL;
                    std::string stationName;
                    int platformNumber = -1;

                    //TODO: use gtest to test if the station was actually found
                    for (TiXmlElement* stationChildElement = tramChildElement->FirstChildElement();
                         stationChildElement != NULL; stationChildElement = stationChildElement->NextSiblingElement()) {
                        if (!strcmp(stationChildElement->Value(), "naam")) {
                            station = metroNet->getStation(stationChildElement->GetText());
                            stationName = stationChildElement->GetText();
                        } else if (!strcmp(stationChildElement->Value(), "perron")) {
                            platformNumber = metro_utils::stoi(stationChildElement->GetText());
                        } else {
                            if (!debug) std::cerr << " unrecognized element '" << stationChildElement->Value() << "' within station" << std::endl;
                            throw MetroNetParseException();
                        }
                    }

                    if (station) {

                        if (platformNumber > 0) {

                            if (station->getType() == UNDERGROUND) {

                                MetroStation* metroStation = (MetroStation*) station;

                                beginPlatform = metroStation->getPlatform(platformNumber);

                            } else {

                                TramStop* tramStop = (TramStop*) station;

                                if (tramStop->getPlatform()->getNumber() == platformNumber) {
                                    beginPlatform = tramStop->getPlatform();
                                }
                            }
                        } else {
                            if (!debug) std::cerr << "invalid platform number given (" << platformNumber << ")" << std::endl;
                            throw MetroNetParseException();
                        }
                    } else {
                        if (!debug) std::cerr << "no station '" << stationName << "' exists within the metronet" << std::endl;
                        throw MetroNetParseException();
                    }

                    if (!beginPlatform) {
                        if (!debug) std::cerr << "no platform exists at station '" << stationName << "' with number " << platformNumber << std::endl;
                        throw MetroNetParseException();
                    }
                }
            }

            if (!line) {
                if (!debug) std::cerr << " no line was parsed from the xml " << std::endl;
                throw MetroNetParseException();
            }

            Tram* tram = NULL;

            if (type == "PCC") {
                tram = new PCC(line, vechicleNumber, beginPlatform);
            } else if (type == "Albatros") {
                if (line->completelyUnderground()) {
                    tram = new Albatros(line, vechicleNumber, beginPlatform);
                } else {
                    if (!debug) std::cerr << "Creating an albatros which would stop at a (above ground) TramStop. Albatros can't go there" << std::endl;
                    throw MetroNetParseException();
                }
            } else if (type == "Tram") {
                tram = new Tram(line, beginPlatform, speed, amountOfSeats, vechicleNumber, length, type);
            } else {
                if (!debug) std::cerr << "Metro Parser: unable to recognize tram type" << std::endl;
                throw MetroNetParseException();
            }

            metroNet->addTram(tram);
            if (!beginPlatform->hasCurrentTram()) {
                beginPlatform->setCurrentTram(tram);
            } else {
                if (!debug) std::cerr << "Another tram cannot be added onto the beginPlatform: it already has a tram and the maximum capacity is 1" << std::endl;
                throw MetroNetParseException();
            }

            // TODO check if there is a way for the tram to reach all its stations in the line (and back)
        }
    }

    const char* MetroNetParseException::what() const throw() {
        return "A metronet parse exception occurred";
    }

    // TODO tram: je moet een gegeven spoor ook meegeven met uw beginstation, tenzij er geen dubbelzinnigheid bestaat
    MetroNet* parseMetroNetXml(const string& filename, bool debug) {
        /// Opens file in doc
        TiXmlDocument doc;
        if (!doc.LoadFile(filename.c_str())) {
            if (!debug) std::cerr << doc.ErrorDesc() << std::endl;
            throw MetroNetParseException();
        }

        /// Loads first child element ("MetroNet") in root
        TiXmlElement* root = doc.FirstChildElement();
        if (root == NULL) {
            doc.Clear();
            if (!debug) std::cerr << "Failed to load file: No root element." << std::endl;
            throw metro_parser::MetroNetParseException();
        }
        //TODO: fix bug with "station=name" (|name| > 1)
        /// Get the Metronet name
        string metroNetName = root->Attribute("naam");
        MetroNet* metroNet = new MetroNet(metroNetName);

        for (TiXmlElement* rootElement = root->FirstChildElement(); rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {
            if (!strcmp(rootElement->Value(), "STATION")) {
                parseStation(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "LIJN")) {
                parseLine(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "TRAM")) {
                parseTram(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "TRACK")) {
                parseTrack(metroNet, rootElement, debug);
            } else {
                if (!debug) std::cerr << "Failed to load file: Unrecognized element '" << rootElement->Value() << "' " << std::endl;
                throw MetroNetParseException();
            }
        }

        return metroNet;
    }
}