//
// Created by Rob Mandelings on 5/03/2020.
//

#include "LineNode.h"
#include "Station.h"

LineNode::LineNode(int lineIndex, Station* station) :
        m_underConstruction(false),
        m_line(lineIndex),
        m_station(station),
        m_previousNode(NULL),
        m_nextNode(NULL) {
    LineNode::_initCheck = this;
    ENSURE(m_line>=0, "Line must be a positive number.");
    ENSURE(m_station!=NULL && m_station->properlyInitialized(), "Station cannot be NULL.");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

LineNode::LineNode(int lineIndex, Station* station, LineNode* previousNode, LineNode* nextNode) :
        m_underConstruction(false),
        m_line(lineIndex),
        m_station(station),
        m_previousNode(previousNode),
        m_nextNode(nextNode) {
    LineNode::_initCheck = this;
    ENSURE(m_line>=0, "Line must be a positive number.");
    ENSURE(m_station!=NULL && m_station->properlyInitialized(),"Station cannot be NULL.");
    ENSURE(m_previousNode!=NULL && m_previousNode->properlyInitialized(), "Node cannot be NULL.");
    ENSURE(m_nextNode!=NULL && m_nextNode->properlyInitialized(), "Node cannot be NULL");
    ENSURE(this->properlyInitialized(),"Constructor must end ...");
}

Station* LineNode::getStation() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(m_station!=NULL && m_station->properlyInitialized(),"Station cannot be NULL.");
    return m_station;
}

LineNode* LineNode::getPreviousNode() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(m_previousNode!=NULL && m_previousNode->properlyInitialized(),"Node cannot be NULL.");
    return m_previousNode;
}

LineNode* LineNode::getNextNode() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(m_nextNode!=NULL && m_nextNode->properlyInitialized(),"Node cannot be NULL.");
    return m_nextNode;
}

void LineNode::setPreviousNode(LineNode* PreviousNode) {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    m_previousNode = PreviousNode;
    ENSURE(m_previousNode == PreviousNode, "m_previousNode must be set to PreviousNode.");
}

void LineNode::setNextNode(LineNode* NextNode) {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    m_nextNode = NextNode;
    ENSURE(m_nextNode == NextNode, "m_nextNode must be set to NextNode.");
}

void LineNode::setUnderConstruction(bool underConstruction) {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    m_underConstruction = underConstruction;
    ENSURE(this->isUnderConstruction() == underConstruction, "m_underConstruction must be set to underConstruction.");
}

bool LineNode::isUnderConstruction() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    return m_underConstruction;
}

bool LineNode::properlyInitialized() const {
    return _initCheck == this;
}
