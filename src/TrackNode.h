//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

class Track;
class Station;

class TrackNode {

private:

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

    void setPreviousNode(TrackNode* previousNode);

    void setNextNode(TrackNode* nextNode);

};
