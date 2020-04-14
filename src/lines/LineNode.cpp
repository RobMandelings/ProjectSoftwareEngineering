//
// Created by Rob Mandelings on 5/03/2020.
//

#include "LineNode.h"
#include "Station.h"

LineNode::LineNode(int lineIndex, Platform* platform) :
        m_underConstruction(false),
        m_line(lineIndex),
        m_platform(platform),
        m_previousNode(NULL),
        m_nextNode(NULL) {
    LineNode::_initCheck = this;
    ENSURE(m_line >= 0, "Line must be a positive number.");
    ENSURE(m_platform != NULL && m_platform->properlyInitialized(), "Station cannot be NULL.");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

LineNode::LineNode(int lineIndex, Platform* platform, LineNode* previousNode, LineNode* nextNode) :
        m_underConstruction(false),
        m_line(lineIndex),
        m_platform(platform),
        m_previousNode(previousNode),
        m_nextNode(nextNode) {
    LineNode::_initCheck = this;
    ENSURE(m_line >= 0, "Line must be a positive number.");
    ENSURE(m_platform != NULL && m_platform->properlyInitialized(), "Station cannot be NULL.");
    ENSURE(m_previousNode != NULL && m_previousNode->properlyInitialized(), "Node cannot be NULL.");
    ENSURE(m_nextNode != NULL && m_nextNode->properlyInitialized(), "Node cannot be NULL");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Station* LineNode::getStation() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(m_platform != NULL && m_platform->properlyInitialized(), "Platform cannot be NULL.");
    REQUIRE(m_platform->getStation() != NULL, " The station of the platform cannot be NULL.");
    return m_platform->getStation();
}

Platform* LineNode::getPlatform() const {
    REQUIRE(m_platform, "The platform cannot be null");
    return m_platform;
}

Platform* LineNode::getNextPlatform() const {
    REQUIRE(getNextNode() != NULL, "The next node cannot be null");
    REQUIRE(getNextNode()->getPlatform() != NULL, "The platform of the next node cannot be null");
    return getNextNode()->getPlatform();
}

Platform* LineNode::getPreviousPlatform() const {
    REQUIRE(getPreviousNode() != NULL, "The previous node cannot be null");
    REQUIRE(getPreviousNode()->getPlatform() != NULL, "The platform of the previous node cannot be null");
    return getPreviousNode()->getPlatform();
}

Station* LineNode::getNextStation() const {
    REQUIRE(getNextNode() != NULL, " The previous node must not be null");
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(getNextNode()->getStation() != NULL && getNextNode()->getStation()->properlyInitialized(), "Station cannot be NULL.");
    return getNextNode()->getStation();
}

Station* LineNode::getPreviousStation() const {
    REQUIRE(getPreviousNode() != NULL, " The previous node must not be null");
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    REQUIRE(getPreviousNode()->getStation() != NULL && getPreviousNode()->getStation()->properlyInitialized(), "Station cannot be NULL.");
    return getPreviousNode()->getStation();
}

LineNode* LineNode::getPreviousNode() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
    return m_previousNode;
}

LineNode* LineNode::getNextNode() const {
    REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
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
