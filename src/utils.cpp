//
// Created by thibaultpoels on 27/02/2020.
//

#include "utils.h"
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

struct StationHolder {

    Station* station;
    string volgende;
    string vorige;

    explicit StationHolder(Station* station) : station(station) {}
};

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
        vector<StationHolder> stationHolders;
        for(TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()){
            if(!strcmp(root_elem->Value(), "STATION")){
                Station* currentStation = new Station();
                StationHolder stationHolder(currentStation);
                for(TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                    elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if(elemName == "naam") {
                        string name = elem->GetText();
                        currentStation->setName(name);
                    } else if(elemName == "volgende") {
                        string volgende = elem->GetText();
                        stationHolder.volgende = volgende;
                    } else if(elemName == "vorige"){
                        string vorige = elem->GetText();
                        stationHolder.vorige = vorige;
                    } else if(elemName == "spoor"){
                        int spoor = stoi(elem->GetText());
                        currentStation->setTrack(spoor);
                    }
                }
                m->addStation(currentStation);
                stationHolders.push_back(stationHolder);
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
                        Station* station = m->getStation(elem->GetText());
                        currentTram->setBeginStation(station);
                    }
                }
                m->addTram(currentTram);
            } else {
                std::cerr << "Failed to load file: Unrecognized element." << std::endl;
            }

            for(vector<StationHolder>::iterator it = stationHolders.begin(); it != stationHolders.end(); ++it){
                it->station->setNext(m->getStation(it->volgende));
                it->station->setPrevious(m->getStation(it->vorige));
            }
        }
        return m;
    }
}