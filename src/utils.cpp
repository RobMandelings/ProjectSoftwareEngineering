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
};

namespace utils{

    int stoi(string input){
        int i;
        istringstream(input) >> i;
        return i;
    }

    MetroNet* parseMetroNet(const char* filename){
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
        vector<StationHolder> holders;
        for(TiXmlElement* root_elem = root->FirstChildElement(); root_elem != NULL; root_elem = root_elem->NextSiblingElement()){
            if(!strcmp(root_elem->Value(), "STATION")){
                Station* s = new Station();
                StationHolder sh;
                for(TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                    elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if(elemName == "naam") {
                        string name = elem->GetText();
                        s->setName(name);
                    } else if(elemName == "volgende") {
                        string volgende = elem->GetText();
                        sh.station = s;
                        sh.volgende = volgende;
                    } else if(elemName == "vorige"){
                        string vorige = elem->GetText();
                        sh.vorige = vorige;
                    } else if(elemName == "spoor"){
                        int spoor = stoi(elem->GetText());
                        s->setTrack(spoor);
                    }
                }
                m->addStation(s);
                holders.push_back(sh);
            } else if(!strcmp(root_elem->Value(), "TRAM")){
                Tram* t = new Tram();
                for(TiXmlElement* elem = root_elem->FirstChildElement(); elem != NULL;
                    elem = elem->NextSiblingElement()) {
                    string elemName = elem->Value();
                    if(elemName == "lijn") {
                        int lijn = stoi(elem->GetText());
                        t->setTramLine(lijn);
                    } else if(elemName == "zitplaatsen") {
                        int zitplaatsen = stoi(elem->GetText());
                        t->setAmountOfSeats(zitplaatsen);
                    } else if(elemName == "snelheid"){
                        int snelheid = stoi(elem->GetText());
                        t->setSpeed(snelheid);
                    } else if(elemName == "beginStation"){
                        string station = elem->GetText();
                        Station* s = m->getStation(station);
                        t->setBeginStation(s);
                    }
                }
                m->addTram(t);
            } else {
                std::cerr << "Failed to load file: Unrecognized element." << std::endl;
            }

            for(vector<StationHolder>::iterator it = holders.begin(); it != holders.end(); ++it){
                it->station->setNext(m->getStation(it->volgende));
                it->station->setPrevious(m->getStation(it->vorige));
            }
        }
        return m;
    }
}

