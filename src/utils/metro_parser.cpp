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

namespace metro_parser {
    const char* MetroNetParseException::what() const throw() {
        return "A metronet parse exception occurred";
    }

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
        //TODO: REQUIRE gtest keywords for exception handling
        //TODO: check if ->Value(), ->Attribute() exists before giving their results to object member vars
        /// Get the Metronet name
        string metroNetName = root->Attribute("naam");
        MetroNet* metroNet = new MetroNet(metroNetName);

        for (TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()) {
            if (!strcmp(root_elem->Value(), "STATION")) {
                std::string stationType;
                for (TiXmlElement *elem = root_elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if (elemName == "type") {
                        stationType = elem->GetText();
                    }
                }
                Station *currentStation = NULL;
                if (stationType == "MetroStation") {
                    currentStation = new MetroStation();
                } else if (stationType == "TramStop") {
                    currentStation = new TramStop();
                }
                string name = root_elem->Attribute("naam");
                currentStation->setName(name);
                metroNet->addStation(currentStation);
            } else if (!strcmp(root_elem->Value(), "LIJN")) {
                Line *currentLine = new Line();
                int lineIndex = metro_utils::stoi(root_elem->Attribute("index"));
                currentLine->setLineIndex(lineIndex);
                for (TiXmlElement *elem = root_elem->FirstChildElement();
                     elem != NULL; elem = elem->NextSiblingElement()) {
                    if (!strcmp(elem->Value(), "LIJNNODE")) {
                        Station *station = metroNet->getStation(elem->Attribute("station"));
                        if (station) {
                            station->addLine(currentLine);
                            LineNode *node = new LineNode(lineIndex, metroNet->getStation(elem->Attribute("station")));
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
            } else if (!strcmp(root_elem->Value(), "TRAM")) {

                int line = -1;
                int amountOfSeats = -1;
                double speed = -1;
                double length = -1;
                LineNode *beginNode = NULL;
                std::string type = "Tram";

                for (TiXmlElement *elem = root_elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if (elemName == "lijn") {
                        line = metro_utils::stoi(elem->GetText());
                    } else if (elemName == "type") {
                        type = elem->GetText();
                    } else if (elemName == "length") {
                        length = metro_utils::stod(elem->GetText());
                    }
                    //TODO what to do if the type is not a default tram but PCC for example? 'zitplaatsen' should not be used in this case
                    if (elemName == "zitplaatsen") {
                        amountOfSeats = metro_utils::stoi(elem->GetText());
                    } else if (elemName == "snelheid") {
                        speed = metro_utils::stod(elem->GetText());
                    } else if (elemName == "beginStation") {
                        //TODO: use gtest to test if the station was actually found
                        beginNode = metroNet->getLine(line)->getNodeForStation(metroNet->getStation(elem->GetText()));
                    }
                }
                if (type == "PCC") {
                    metroNet->addTram(new PCC(line, beginNode));
                } else if (type == "Albatros") {
                    metroNet->addTram(new Albatros(line, beginNode));
                } else if (type == "Tram"){
                    metroNet->addTram(new Tram(line, beginNode, speed, amountOfSeats, length, type));
                } else {
                    if (!debug) std::cerr << "Metro Parser: unable to recognize tram type" << std::endl;
                    throw MetroNetParseException();
                }
            } else {
                if (!debug) std::cerr << "Failed to load file: Unrecognized element." << std::endl;
                throw MetroNetParseException();
            }
        }
        return metroNet;
    }
}