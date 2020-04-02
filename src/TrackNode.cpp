//
// Created by Rob Mandelings on 5/03/2020.
//

#include "TrackNode.h"
#include "Station.h"

TrackNode::TrackNode(int trackIndex, Station* station) :
        m_underConstruction(false),
        m_line(trackIndex),
        m_station(station),
        m_previousNode(NULL),
        m_nextNode(NULL) {
    TrackNode::_initCheck = this;
    ENSURE(m_line>=0, "Line must be a positive number.");
    ENSURE(m_station->properlyInitialized(), "Station cannot be NULL.");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

TrackNode::TrackNode(int trackIndex, Station* station, TrackNode* previousNode, TrackNode* nextNode) :
        m_underConstruction(false),
        m_line(trackIndex),
        m_station(station),
        m_previousNode(previousNode),
        m_nextNode(nextNode) {
    TrackNode::_initCheck = this;
    ENSURE(m_line>=0, "Line must be a positive number.");
    ENSURE(m_station->properlyInitialized(),"Station cannot be NULL.");
    ENSURE(m_previousNode->properlyInitialized(), "Node cannot be NULL.");
    ENSURE(nextNode->properlyInitialized(), "Node cannot be NULL");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Station* TrackNode::getStation() const {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    ENSURE(m_station->properlyInitialized(),"Station cannot be NULL.");
    return m_station;
}

TrackNode* TrackNode::getPreviousNode() const {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    return m_previousNode;
}

TrackNode* TrackNode::getNextNode() const {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    return m_nextNode;
}

void TrackNode::setPreviousNode(TrackNode* PreviousNode) {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    REQUIRE(PreviousNode->properlyInitialized(), "A new node cannot be NULL.");
    m_previousNode = PreviousNode;
}

void TrackNode::setNextNode(TrackNode* NextNode) {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    REQUIRE(NextNode->properlyInitialized(), "A new node cannot be NULL");
    m_nextNode = NextNode;
}

void TrackNode::setUnderConstruction(bool underConstruction) {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    m_underConstruction = underConstruction;
    
}

bool TrackNode::isUnderConstruction() const {
    REQUIRE(this->properlyInitialized(), "TrackNode must be initialized before its member variables are used.");
    return m_underConstruction;
}

bool TrackNode::properlyInitialized() const {
    return _initCheck == this;
}
