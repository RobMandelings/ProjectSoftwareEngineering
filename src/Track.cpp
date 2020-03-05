//
// Created by Rob Mandelings on 5/03/2020.
//

#include "Track.h"

Track::Track(int line, TrackNode* firstNode) :
        m_line(line),
        m_firstNode(firstNode) {}

int Track::getLine() const {
    return m_line;
}

TrackNode* Track::getFirstNode() const {
    return m_firstNode;
}

bool Track::insertNode(const std::string& afterStation, TrackNode* trackNode) {
    //TODO empty method stub
    return false;
}

void Track::setLine(int line) {
    this->m_line = line;
}

Track::Track() {}

bool Track::insertNode(TrackNode *trackNode) {
    //TODO: implement
    return false;
}
