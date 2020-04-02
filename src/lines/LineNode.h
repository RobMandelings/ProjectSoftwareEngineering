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
     */
    LineNode(int line, Station* station);

    /**
     * @brief simple constructor
     * @param line: the line corresponding to this lineNode
     * @param station: the station this lineNode is in
     * @param previousNode
     * @param nextNode
     */
    LineNode(int line, Station* station, LineNode* previousNode, LineNode* nextNode);

    /**
     * @brief simple getter
     * @return the station this linenode is in
     */
    Station* getStation() const;

    /**
     * @brief simple getter
     * @return the previous node of this linenode
     */
    LineNode* getPreviousNode() const;

    /**
     * @brief simple getter
     * @return the next node of this lineNode
     */
    LineNode* getNextNode() const;

    /**
     * @brief simple setter
     * @param underConstruction: true if the lineNode should be marked as 'under construction', false if not
     */
    void setUnderConstruction(bool underConstruction);

    /**
     * @brief simple getter
     * @return if the lineNode is under construction
     */
    bool isUnderConstruction() const;

    /**
     * @brief simple setter
     * @param previousNode the previousNode of this lineNode
     */
    void setPreviousNode(LineNode* previousNode);

    /**
     * @brief simple setter
     * @param nextNode the next node of this LineNode
     */
    void setNextNode(LineNode* nextNode);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};
