//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include "library.h"

class Line;

class Station;

//TODO test lineNode is circular (has next and previous for each lineNode)
class LineNode {

private:

    bool m_underConstruction;

    int m_line;

    Station* m_station;

    LineNode* m_previousNode;
    LineNode* m_nextNode;

    LineNode* _initCheck;

public:

    /**
     * @brief simple constructor
     * @param line: the line corresponding to this lineNode
     * @param station: the station this lineNode is in
     \n ENSURE(m_line>=0, "Line must be a positive number.");
     \n ENSURE(m_station!=NULL && m_station->properlyInitialized(), "Station cannot be NULL.");
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    LineNode(int line, Station* station);

    /**
     * @brief simple constructor
     * @param line: the line corresponding to this lineNode
     * @param station: the station this lineNode is in
     * @param previousNode
     * @param nextNode
     \n ENSURE(m_line>=0, "Line must be a positive number.");
     \n ENSURE(m_station!=NULL && m_station->properlyInitialized(),"Station cannot be NULL.");
     \n ENSURE(m_previousNode!=NULL && m_previousNode->properlyInitialized(), "Node cannot be NULL.");
     \n ENSURE(m_nextNode!=NULL && m_nextNode->properlyInitialized(), "Node cannot be NULL");
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    LineNode(int line, Station* station, LineNode* previousNode, LineNode* nextNode);

    /**
     * @brief simple getter
     * @return the station this linenode is in
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n REQUIRE(m_station!=NULL && m_station->properlyInitialized(),"Station cannot be NULL.");
     */
    Station* getStation() const;

    /**
     * @brief simple getter
     * @return the previous node of this linenode
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n REQUIRE(m_previousNode!=NULL && m_previousNode->properlyInitialized(),"Node cannot be NULL.");
     */
    LineNode* getPreviousNode() const;

    /**
     * @brief simple getter
     * @return the next node of this lineNode
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n REQUIRE(m_nextNode!=NULL && m_nextNode->properlyInitialized(),"Node cannot be NULL.");
     */
    LineNode* getNextNode() const;

    /**
     * @brief simple setter
     * @param underConstruction: true if the lineNode should be marked as 'under construction', false if not
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n ENSURE(this->isUnderConstruction() == underConstruction, "m_underConstruction must be set to underConstruction.");
     */
    void setUnderConstruction(bool underConstruction);

    /**
     * @brief simple getter
     * @return if the lineNode is under construction
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     */
    bool isUnderConstruction() const;

    /**
     * @brief simple setter
     * @param previousNode the previousNode of this lineNode
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n ENSURE(m_previousNode == PreviousNode, "m_previousNode must be set to PreviousNode.");
     */
    void setPreviousNode(LineNode* previousNode);

    /**
     * @brief simple setter
     * @param nextNode the next node of this LineNode
     \n REQUIRE(this->properlyInitialized(), "LineNode must be initialized before its member variables are used.");
     \n ENSURE(m_nextNode == NextNode, "m_nextNode must be set to NextNode.");
     */
    void setNextNode(LineNode* nextNode);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};
