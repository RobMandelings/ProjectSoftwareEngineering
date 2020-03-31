//
// Created by Rob Mandelings on 5/03/2020.
//

#include "Track.h"
#include "Station.h"

Track::Track(int line, TrackNode* firstNode) :
        m_line(line),
        m_firstNode(firstNode) {
    Track::_initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}


//TODO test that the line is not -1
//TODO test station is not NULL
Track::Track() : m_line(-1), m_firstNode(NULL) {
    Track::_initCheck = this;
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Track::~Track() {
    if (m_firstNode != NULL) {
        TrackNode* currentTrackNode = m_firstNode;
        do {

            TrackNode* nextTrackNode = currentTrackNode->getNextNode();

            if (nextTrackNode != NULL) {
                nextTrackNode->setPreviousNode(NULL);
            }
            currentTrackNode->setNextNode(NULL);
            delete currentTrackNode;

            currentTrackNode = nextTrackNode;

        } while (currentTrackNode != NULL);
    }
}

int Track::getLine() const {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
    return m_line;
}

TrackNode* Track::getFirstNode() const {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
    return m_firstNode;
}

void Track::setLine(int line) {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
    this->m_line = line;
}

bool Track::insertNode(TrackNode* trackNode) {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");

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
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");

    TrackNode* trackNode = getNodeForStation(station);

    if (trackNode != NULL) {
        trackNode->setUnderConstruction(true);
        return true;
    }
    return false;
}

TrackNode* Track::getNodeForStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");

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

std::string Track::getAsString() const {
    REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
    std::string trackString;
    if (m_firstNode != NULL) {
        TrackNode* currentTrackNode = m_firstNode;
        do {
            trackString += "Station " + currentTrackNode->getStation()->getName() + " --> ";

            currentTrackNode = currentTrackNode->getNextNode();
        } while (currentTrackNode != NULL && currentTrackNode != m_firstNode);
        trackString += "Station " + m_firstNode->getStation()->getName() + " --> ...";
    }
    return trackString;
}

bool Track::properlyInitialized() const {
    return _initCheck == this;
}