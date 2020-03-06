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

void Track::setLine(int line) {
    this->m_line = line;
}

Track::Track() {}

bool Track::insertNode(TrackNode *trackNode) {

    if (trackNode != NULL) {
        if (m_firstNode == NULL) {
            m_firstNode = trackNode;
            m_firstNode->setPreviousNode(trackNode);
            m_firstNode->setNextNode(trackNode);

            return true;

        } else {
            TrackNode* lastNode = m_firstNode->getPreviousNode();
            trackNode->setNextNode(m_firstNode);
            trackNode->setPreviousNode(lastNode);

            lastNode->setNextNode(trackNode);
            m_firstNode->setPreviousNode(trackNode);

            return true;
        }
    }
    return false;
}

bool Track::disableNodeForStation(Station* station) {

    if (m_firstNode != NULL && station != NULL) {
        TrackNode* trackNode = m_firstNode;

        do {

            if (trackNode->getStation() == station) {
                trackNode->setUnderConstruction(true);
                return true;
            }

            trackNode = trackNode->getNextNode();

        } while (trackNode != NULL && trackNode != m_firstNode);
    }
    return false;
}
