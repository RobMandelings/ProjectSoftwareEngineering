//
// Created by Rob Mandelings on 6/03/2020.
//

#include "metro_parser.h"
#include "../MetroNet.h"
#include "../Tram.h"
#include "../Station.h"
#include "../Track.h"
#include "../TrackNode.h"
#include "metro_utils.h"

MetroNet* metro_parser::parseMetroNetXml(const char* filename) {
    /// Opens file in doc
    TiXmlDocument doc;
    if (!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    /// Loads first child element ("MetroNet") in root
    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return NULL;
    }

    //TODO fix bug with "station=name" (|name| > 1)
    //TODO: REQUIRE gtest keywords for exception handling
    MetroNet* metroNet = new MetroNet("Antwerpen");
    for (TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()) {
        if (!strcmp(root_elem->Value(), "STATION")) {
            Station* currentStation = new Station();
            string name = root_elem->Attribute("naam");
            currentStation->setName(name);
            metroNet->addStation(currentStation);
        } else if (!strcmp(root_elem->Value(), "LIJN")) {
            Track* currentTrack = new Track();
            int line = metro_utils::stoi(root_elem->Attribute("index"));
            currentTrack->setLine(line);
            for (TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                if (!strcmp(elem->Value(), "LIJNNODE")) {
                    Station* station = metroNet->getStation(elem->Attribute("station"));
                    if (station) {
                        station->addTrack(currentTrack);
                        TrackNode* node = new TrackNode(line, metroNet->getStation(elem->Attribute("station")));
                        currentTrack->insertNode(node);
                    } else {
                        cerr << "MetroParser: Station with name " << elem->Attribute("station") << " wasn't found" << endl;
                    }
                }
            }
            metroNet->addTrack(currentTrack);
        } else if (!strcmp(root_elem->Value(), "TRAM")) {

            int line = 0;
            int amountOfSeats = 0;
            int speed = 0;
            TrackNode* beginNode = NULL;

            for (TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                if (elemName == "lijn") {
                    line = metro_utils::stoi(elem->GetText());
                } else if (elemName == "zitplaatsen") {
                    amountOfSeats = metro_utils::stoi(elem->GetText());
                } else if (elemName == "snelheid") {
                    speed = metro_utils::stoi(elem->GetText());
                } else if (elemName == "beginStation") {
                    //TODO: use gtest to test if the station was actually found
                    beginNode = metroNet->getTrack(line)->getNodeForStation(metroNet->getStation(elem->GetText()));
                }
            }
            metroNet->addTram(new Tram(line, speed, amountOfSeats, beginNode));
        } else {
            std::cerr << "Failed to load file: Unrecognized element." << std::endl;
        }
    }
    return metroNet;
}