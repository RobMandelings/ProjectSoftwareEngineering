//
// Created by jasper on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATION_H
#define PROJECTSOFTWAREENGINEERING_STATION_H

#include "library.h"

class Station {
private:
    string m_name;
    Station* m_next;
    Station* m_previous;
    int m_track;
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
