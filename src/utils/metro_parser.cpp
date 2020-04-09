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

namespace metro_parser {

    namespace {

        void parseStation(MetroNet* metroNet, TiXmlElement* stationTag, bool debug) {

            std::string stationType;
            std::vector<Platform*> platforms;

            for (TiXmlElement* currentChildElement = stationTag->FirstChildElement(); currentChildElement != NULL;
                 currentChildElement = currentChildElement->NextSiblingElement()) {
                string childElementName = currentChildElement->Value();
                if (childElementName == "type") {
                    stationType = currentChildElement->GetText();
                } else if (childElementName == "perron") {
                    int platformNumber = -1;
                    for (TiXmlElement* currentPerronChildElement = currentChildElement->FirstChildElement();
                         currentPerronChildElement != NULL; currentPerronChildElement = currentPerronChildElement->NextSiblingElement()) {
                        if (!strcmp(currentPerronChildElement->Value(), "nummer")) {
                            platformNumber = metro_utils::stoi(currentPerronChildElement->GetText());
                        }
                    }
                    if (platformNumber < 0) {
                        throw MetroNetParseException();
                    } else {
                        platforms.push_back(new Platform(platformNumber));
                    }
                }
            }

            if (platforms.empty()) {
                throw MetroNetParseException();
            }
            Station* currentStation = NULL;
            if (stationType == "MetroStation") {
                MetroStation* metroStation = new MetroStation();
                metroStation->getPlatforms();
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {
                    metroStation->addPlatform(*it);
                }
                currentStation = metroStation;
            } else if (stationType == "TramStop") {
                if (platforms.size() > 1) {
                    throw MetroNetParseException();
                } else {
                    currentStation = new TramStop(platforms.at(0));
                }
            } else {
                throw MetroNetParseException();
            }

            // The station of the platform is set to the currentStation
            for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); it++) {
                (*it)->setStation(currentStation);
            }
            string name = stationTag->Attribute("naam");
            currentStation->setName(name);
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

            int lineIndex = -1;
            int amountOfSeats = -1;
            int voertuigNr = -1;
            double speed = -1;
            double length = -1;
            Station* beginStation = NULL;
            std::string type = "Tram";

            for (TiXmlElement* tag = tramElement->FirstChildElement(); tag != NULL;
                 tag = tag->NextSiblingElement()) {
                string tagName = tag->Value();
                if (tagName == "lijn") {
                    lineIndex = metro_utils::stoi(tag->GetText());
                } else if (tagName == "type") {
                    type = tag->GetText();
                } else if (tagName == "length") {
                    length = metro_utils::stod(tag->GetText());
                } else if (tagName == "voertuigNr") {
                    voertuigNr = metro_utils::stoi(tag->GetText());
                }
                //TODO what to do if the type is not a default tram but PCC for example? 'zitplaatsen' should not be used in this case
                if (tagName == "zitplaatsen") {
                    amountOfSeats = metro_utils::stoi(tag->GetText());
                } else if (tagName == "snelheid") {
                    speed = metro_utils::stod(tag->GetText());
                } else if (tagName == "beginStation") {
                    //TODO: use gtest to test if the station was actually found
                    beginStation = metroNet->getStation(tag->GetText());
                }
            }
            if (type == "PCC") {
                metroNet->addTram(new PCC(metroNet->getLine(lineIndex), voertuigNr, beginStation));
            } else if (type == "Albatros") {
                metroNet->addTram(new Albatros(metroNet->getLine(lineIndex), voertuigNr, beginStation));
            } else if (type == "Tram") {
                metroNet->addTram(new Tram(metroNet->getLine(lineIndex), beginStation, NULL, speed, amountOfSeats, voertuigNr, length, type));
            } else {
                if (!debug) std::cerr << "Metro Parser: unable to recognize tram type" << std::endl;
                throw MetroNetParseException();
            }
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

        for (TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()) {
            if (!strcmp(root_elem->Value(), "STATION")) {
                parseStation(metroNet, root_elem, debug);
            } else if (!strcmp(root_elem->Value(), "LIJN")) {
                parseLine(metroNet, root_elem, debug);
            } else if (!strcmp(root_elem->Value(), "TRAM")) {
                parseTram(metroNet, root_elem, debug);
            } else {
                if (!debug) std::cerr << "Failed to load file: Unrecognized element." << std::endl;
                throw MetroNetParseException();
            }
        }
        return metroNet;
    }
}