//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include <string>
#include "TrackNode.h"

class Track {

private:

    int m_line;
    TrackNode* m_firstNode;

public:

    Track(int line, TrackNode* firstNode);

    Track();

    void setLine(int line);

    int getLine() const;

    TrackNode* getFirstNode() const;

    /**
     * Inserts a node as the last element of the track
     * @param trackNode the node you want to add to the track
     * @return true if the operation was successful
     */
    bool insertNode(TrackNode* trackNode);

};