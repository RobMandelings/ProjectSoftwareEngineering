//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include "library.h"

class Track;

class Station;

//TODO test trackNode is circular (has next and previous for each trackNode)
class TrackNode {

private:

    bool m_underConstruction;

    int m_line;

    Station* m_station;

    TrackNode* m_previousNode;
    TrackNode* m_nextNode;

    TrackNode* _initCheck;

public:

    /**
     * @brief simple constructor
     * @param line: the line corresponding to this trackNode
     * @param station: the station this trackNode is in
     */
    TrackNode(int line, Station* station);

    /**
     * @brief simple constructor
     * @param line: the line corresponding to this trackNode
     * @param station: the station this trackNode is in
     * @param previousNode
     * @param nextNode
     */
    TrackNode(int line, Station* station, TrackNode* previousNode, TrackNode* nextNode);

    /**
     * @brief simple getter
     * @return the station this tracknode is in
     */
    Station* getStation() const;

    /**
     * @brief simple getter
     * @return the previous node of this tracknode
     */
    TrackNode* getPreviousNode() const;

    /**
     * @brief simple getter
     * @return the next node of this trackNode
     */
    TrackNode* getNextNode() const;

    /**
     * @brief simple setter
     * @param underConstruction: true if the trackNode should be marked as 'under construction', false if not
     */
    void setUnderConstruction(bool underConstruction);

    /**
     * @brief simple getter
     * @return if the trackNode is under construction
     */
    bool isUnderConstruction() const;

    /**
     * @brief simple setter
     * @param previousNode the previousNode of this trackNode
     */
    void setPreviousNode(TrackNode* previousNode);

    /**
     * @brief simple setter
     * @param nextNode the next node of this TrackNode
     */
    void setNextNode(TrackNode* nextNode);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};
