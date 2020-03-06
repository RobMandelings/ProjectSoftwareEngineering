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

    bool insertNode(TrackNode* trackNode);

};