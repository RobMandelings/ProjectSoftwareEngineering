//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once


#include "TrackNode.h"

class Track {

private:

    int m_line;
    TrackNode* m_firstNode;

public:

    Track(int line, TrackNode* firstNode);

    int getLine() const;

    TrackNode* getFirstNode() const;

};