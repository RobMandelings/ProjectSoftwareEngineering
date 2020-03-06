//
// Created by Rob Mandelings on 5/03/2020.
//

#include "TrackNode.h"

TrackNode::TrackNode(int trackIndex, Station* station) :
        m_underConstruction(false),
        m_line(trackIndex),
        m_station(station),
        m_previousNode(NULL),
        m_nextNode(NULL) {}

TrackNode::TrackNode(int trackIndex, Station* station, TrackNode* previousNode, TrackNode* nextNode) :
        m_underConstruction(false),
        m_line(trackIndex),
        m_station(station),
        m_previousNode(previousNode),
        m_nextNode(nextNode) {}

Station* TrackNode::getStation() const {
    return m_station;
}

TrackNode* TrackNode::getPreviousNode() const {
    return m_previousNode;
}

TrackNode* TrackNode::getNextNode() const {
    return m_nextNode;
}

void TrackNode::setPreviousNode(TrackNode* PreviousNode) {
    m_previousNode = PreviousNode;
}

void TrackNode::setNextNode(TrackNode* NextNode) {
    m_nextNode = NextNode;
}

void TrackNode::setUnderConstruction(bool underConstruction) {
    m_underConstruction = underConstruction;
}

bool TrackNode::isUnderConstruction() const {
    return m_underConstruction;
}
