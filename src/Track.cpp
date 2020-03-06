//
// Created by Rob Mandelings on 5/03/2020.
//

#include "Track.h"
#include "Station.h"

Track::Track(int line, TrackNode* firstNode) :
        m_line(line),
        m_firstNode(firstNode) {}

Track::Track() : m_line(-1), m_firstNode(NULL) {}

int Track::getLine() const {
    return m_line;
}

TrackNode* Track::getFirstNode() const {
    return m_firstNode;
}

void Track::setLine(int line) {
    this->m_line = line;
}

bool Track::insertNode(TrackNode* trackNode) {

    if (trackNode != NULL) {
        if (m_firstNode == NULL) {
            m_firstNode = trackNode;
            m_firstNode->setPreviousNode(trackNode);
            m_firstNode->setNextNode(trackNode);

        } else {
            TrackNode* lastNode = m_firstNode->getPreviousNode();
            trackNode->setNextNode(m_firstNode);
            trackNode->setPreviousNode(lastNode);

            lastNode->setNextNode(trackNode);
            m_firstNode->setPreviousNode(trackNode);
        }

        return true;
    }
    return false;
}

bool Track::disableNodeForStation(Station* station) {

    TrackNode* trackNode = getNodeForStation(station);

    if (trackNode != NULL) {
        trackNode->setUnderConstruction(true);
        return true;
    }
    return false;
}

TrackNode* Track::getNodeForStation(Station* station) {

    if (m_firstNode != NULL && station != NULL) {
        TrackNode* trackNode = m_firstNode;

        do {

            if (trackNode->getStation() == station) {
                return trackNode;
            }

            trackNode = trackNode->getNextNode();

        } while (trackNode != NULL && trackNode != m_firstNode);
    }
    return NULL;
}

void Track::traverse() const {
    if (m_firstNode != NULL) {
        TrackNode* currentTrackNode = m_firstNode;
        do {
            cout << currentTrackNode->getStation()->getName() << endl;

            currentTrackNode = currentTrackNode->getNextNode();
        } while (currentTrackNode != NULL && currentTrackNode != m_firstNode);
    }
}
