//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include "library.h"

class Track;
class Station;

class TrackNode {

private:

    bool m_underConstruction;

    int m_line;

    Station* m_station;

    TrackNode* m_previousNode;
    TrackNode* m_nextNode;

public:

    TrackNode(int line, Station* station);

    TrackNode(int line, Station* station, TrackNode* previousNode, TrackNode* nextNode);

    Station* getStation() const;

    TrackNode* getPreviousNode() const;

    TrackNode* getNextNode() const;

    void setUnderConstruction(bool underConstruction);

    bool isUnderConstruction() const;

    void setPreviousNode(TrackNode* previousNode);

    void setNextNode(TrackNode* nextNode);

};
