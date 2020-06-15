//
// Created by Rob Mandelings on 5/03/2020.
//

#include "Line.h"
#include "Station.h"
#include "Tram.h"

Line::Line(int line, LineNode* firstNode) :
        m_lineNumber(line),
        m_firstNode(firstNode) {
    Line::_initCheck = this;
    ENSURE(m_lineNumber >= 0, "Line must be a positive number.");
    ENSURE(m_firstNode != NULL && m_firstNode->properlyInitialized(), "The first node cannot be NULL.");
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Line::Line() : m_lineNumber(-1), m_firstNode(NULL) {
    Line::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Line::~Line() {

    std::vector<LineNode*> lineAsVector = getAsVector();

    for (std::vector<LineNode*>::iterator it = lineAsVector.begin(); it != lineAsVector.end(); it++) {
        
        
        
    }
}

bool Line::completelyUnderground() const {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(m_firstNode != NULL, "The first node of this line cannot be null");

    LineNode* currentNode = m_firstNode;

    do {

        if (currentNode->getStation()->getType() == ABOVE_GROUND) {
            return false;
        }

        currentNode = currentNode->getNextNode();

    } while (currentNode != m_firstNode);

    return true;
}

int Line::getLineNumber() const {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(m_lineNumber >= 0, "Line cannot be a negative number.");
    return m_lineNumber;
}

LineNode* Line::getFirstNode() const {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(m_firstNode != NULL && m_firstNode->properlyInitialized(), "The first node cannot be NULL.");
    return m_firstNode;
}

void Line::setLineNumber(int line) {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(line >= 0, "Line must be a positive number.");
    this->m_lineNumber = line;
    ENSURE(m_lineNumber == line, "m_line must be set to line.");
}

void Line::insertNode(LineNode* lineNode) {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(lineNode != NULL && lineNode->properlyInitialized(), "A line node cannot be NULL.");
    
    unsigned int oldSize = this->getAsVector().size();

    if (m_firstNode == NULL) {
        m_firstNode = lineNode;
        m_firstNode->setPreviousNode(lineNode);
        m_firstNode->setNextNode(lineNode);

    } else {
        LineNode* lastNode = m_firstNode->getPreviousNode();
        lineNode->setNextNode(m_firstNode);
        lineNode->setPreviousNode(lastNode);

        lastNode->setNextNode(lineNode);
        m_firstNode->setPreviousNode(lineNode);
    }

    ENSURE(m_firstNode != NULL && m_firstNode->properlyInitialized(), "After an insert, the first node cannot be NULL.");
    ENSURE(this->getAsVector().size() > oldSize, "A node must be added after insertNode is called.");
}

void Line::disableNodeForStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(station != NULL && station->properlyInitialized(), "Station cannot be NULL.");

    LineNode* lineNode = getNodeForStation(station);

    lineNode->setUnderConstruction(true);
    ENSURE(lineNode->isUnderConstruction(), "The line node must be under construction.");
}

LineNode* Line::getNodeForStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    REQUIRE(station != NULL && station->properlyInitialized(), "Station cannot be NULL.");
    if (m_firstNode != NULL) {
        LineNode* lineNode = m_firstNode;

        do {

            if (lineNode->getStation() == station) {
                ENSURE(lineNode != NULL && lineNode->properlyInitialized(), "The line node cannot be NULL.");
                return lineNode;
            }

            lineNode = lineNode->getNextNode();

        } while (lineNode != NULL && lineNode != m_firstNode);
    }
    return NULL;
}

std::vector<LineNode*> Line::getAsVector() const {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    std::vector<LineNode*> lineAsVector;

    if (m_firstNode != NULL) {
        LineNode* currentLineNode = m_firstNode;

        do {

            lineAsVector.push_back(currentLineNode);

            currentLineNode = currentLineNode->getNextNode();

        } while (currentLineNode != NULL && currentLineNode != m_firstNode);
    }
    return lineAsVector;
}

std::string Line::getAsString() const {
    REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
    std::string lineString;
    if (m_firstNode != NULL) {
        LineNode* currentLineNode = m_firstNode;
        do {
            lineString += "Station " + currentLineNode->getStation()->getName() + " --> ";

            currentLineNode = currentLineNode->getNextNode();
        } while (currentLineNode != NULL && currentLineNode != m_firstNode);
        lineString += "Station " + m_firstNode->getStation()->getName() + " --> ...";
    }
    return lineString;
}

bool Line::properlyInitialized() const {
    return _initCheck == this;
}