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

    bool insertNode(int index, TrackNode* trackNode);

    bool insertNode(const std::string& afterStation, TrackNode* trackNode);

    bool insertNode(TrackNode* trackNode);

};