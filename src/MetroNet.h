//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METRONET_H
#define PROJECTSOFTWAREENGINEERING_METRONET_H

#include "library.h"

class Station;
class Tram;

class MetroNet {
private:
    string name;
    vector<Tram*> trams;
    vector<Station*> stations;
public:
    const string &getName() const;

    void setName(const string &name);

    Tram *getTram(int line) const;

    Station *getStation(string name) const;


    void addStation(Station* station);

    void addTram(Tram* tram);
};


#endif //PROJECTSOFTWAREENGINEERING_METRONET_H
