//
// Created by thibaultpoels on 27/02/2020.
//

#include "utils.h"
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "Track.h"
#include "TrackNode.h"

namespace utils{

    int stoi(const string& input){
        int i;
        istringstream(input) >> i;
        return i;
    }

    MetroNet* parseMetroNetXml(const char* filename){
        /// Opens file in doc
        TiXmlDocument doc;
        if(!doc.LoadFile(filename)) {
            std::cerr << doc.ErrorDesc() << std::endl;
        }

        /// Loads first child element ("MetroNet") in root
        TiXmlElement* root = doc.FirstChildElement();
        if(root == NULL) {
            std::cerr << "Failed to load file: No root element." << std::endl;
            doc.Clear();
        }

        MetroNet* m = new MetroNet();
        m->setName("Antwerpen");
        for(TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()){
            if(!strcmp(root_elem->Value(), "STATION")) {
                Station *currentStation = new Station();
                string name = root_elem->Attribute("naam");
                currentStation->setName(name);
                m->addStation(currentStation);
            } else if(!strcmp(root_elem->Value(), "LIJN")){
                Track* currentTrack = new Track();
                int line = stoi(root_elem->Attribute("index"));
                currentTrack->setLine(line);
                for(TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
                    if(!strcmp(elem->Value(), "LIJNNODE")){
                        Station* st = m->getStation(elem->Attribute("station"));
                        st->addTrack(currentTrack);
                        TrackNode* node = new TrackNode(line,m->getStation(elem->Attribute("station")));
                        currentTrack->insertNode(node);
                    }
                }
            } else if(!strcmp(root_elem->Value(), "TRAM")){
                Tram* currentTram = new Tram();
                for(TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                    elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if(elemName == "lijn") {
                        int lijn = stoi(elem->GetText());
                        currentTram->setTramLine(lijn);
                    } else if(elemName == "zitplaatsen") {
                        int zitplaatsen = stoi(elem->GetText());
                        currentTram->setAmountOfSeats(zitplaatsen);
                    } else if(elemName == "snelheid"){
                        int snelheid = stoi(elem->GetText());
                        currentTram->setSpeed(snelheid);
                    } else if(elemName == "beginStation"){
                        //TODO: get TrackNode
                    }
                }
                m->addTram(currentTram);
            } else {
                std::cerr << "Failed to load file: Unrecognized element." << std::endl;
            }
        }
        return m;
    }
}