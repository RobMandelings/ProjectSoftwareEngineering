//
// Created by jasper on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATION_H
#define PROJECTSOFTWAREENGINEERING_STATION_H

#include "library.h"

class Station {
private:
    string name;
    Station* next;
    Station* previous;
    int track;
public:
    const string& getName() const;

    void setName(const string& name);

    Station* getNext() const;

    void setNext(Station* next);

    Station* getPrevious() const;

    void setPrevious(Station* previous);

    int getTrack() const;

    void setTrack(int track);

};


#endif //PROJECTSOFTWAREENGINEERING_STATION_H
