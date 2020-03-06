//
// Created by Rob Mandelings on 6/03/2020.
//

#include "metroParser.h"
#include "../MetroNet.h"
#include "../Tram.h"
#include "../Station.h"
#include "../Track.h"
#include "../TrackNode.h"
#include "metroUtils.h"

MetroNet* metroParser::parseMetroNetXml(const char* filename) {
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
            int line = metroUtils::stoi(root_elem->Attribute("index"));
            currentTrack->setLine(line);
            for (TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                if (!strcmp(elem->Value(), "LIJNNODE")) {
                    Station* st = metroNet->getStation(elem->Attribute("station"));
                    st->addTrack(currentTrack);
                    TrackNode* node = new TrackNode(line, metroNet->getStation(elem->Attribute("station")));
                    currentTrack->insertNode(node);
                }
            }
            metroNet->addTrack(currentTrack);
        } else if (!strcmp(root_elem->Value(), "TRAM")) {
            Tram* currentTram = new Tram();
            for (TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                if (elemName == "lijn") {
                    int lijn = metroUtils::stoi(elem->GetText());
                    currentTram->setTramLine(lijn);
                } else if (elemName == "zitplaatsen") {
                    int zitplaatsen = metroUtils::stoi(elem->GetText());
                    currentTram->setAmountOfSeats(zitplaatsen);
                } else if (elemName == "snelheid") {
                    int snelheid = metroUtils::stoi(elem->GetText());
                    currentTram->setSpeed(snelheid);
                } else if (elemName == "beginStation") {
                    currentTram->setBeginNode(metroNet->getTrack(currentTram->getTramLine())->getNodeForStation(metroNet->getStation(elem->GetText())));
                }
            }
            metroNet->addTram(currentTram);
        } else {
            std::cerr << "Failed to load file: Unrecognized element." << std::endl;
        }
    }
    return metroNet;
}