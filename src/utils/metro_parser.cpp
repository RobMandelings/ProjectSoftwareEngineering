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
#include "DesignByContract.h"

namespace metro_parser {
    const char* MetroNetParseException::what() const throw() {
        return "A metronet parse exception occurred";
    }

    MetroNet* parseMetroNetXml(const string& filename, bool debug) {
        /// Opens file in doc
        TiXmlDocument doc;
        if (!doc.LoadFile(filename.c_str())) {
            if(!debug) std::cerr << doc.ErrorDesc() << std::endl;
            throw MetroNetParseException();
        }

        /// Loads first child element ("MetroNet") in root
        TiXmlElement* root = doc.FirstChildElement();
        if (root == NULL) {
            doc.Clear();
            if(!debug) std::cerr << "Failed to load file: No root element." << std::endl;
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
                            if(!debug) cerr << "MetroParser: Station with name " << elem->Attribute("station") << " wasn't found" << endl;
                            throw MetroNetParseException();
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
                if(!debug) std::cerr << "Failed to load file: Unrecognized element." << std::endl;
                throw MetroNetParseException();
            }
        }
        ENSURE(metroNet, "MetroNet should not be null at the end of the parser function!");
        return metroNet;
    }
}