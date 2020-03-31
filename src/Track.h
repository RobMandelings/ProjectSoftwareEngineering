//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include <string>
#include "TrackNode.h"
#include "library.h"

class Track {

private:

    int m_line;
    TrackNode* m_firstNode;

    Track* _initCheck;
public:

    /**
     * @brief simple constructor
     * @param line: the line this track is on
     * @param firstNode: the 'entry' node of this track (entry to the linked list of TrackNodes)
     */
    Track(int line, TrackNode* firstNode);

    /**
     * @brief simple constructor
     */
    Track();

    ~Track();

    /**
     * @brief simple setter
     * @param line: the newLine of this track
     */
    void setLine(int line);

    /**
     * @brief simple getter
     * @return the line of this track
     */
    int getLine() const;

    /**
     * @brief simple getter
     * @return the first node / entry node of this track
     */
    TrackNode* getFirstNode() const;

    /**
     * @brief gets the corresponding TrackNode for a given station in this track
     * @param station: pointer to the station you want to get the node for
     * @return: the corresponding track node
     */
    TrackNode* getNodeForStation(Station* station);

    /**
     * Inserts a node as the last element of the track
     * @param trackNode the node you want to add to the track
     * @return true if the operation was successful
     */
    bool insertNode(TrackNode* trackNode);

    /**
     * @brief disables the TrackNode corresponding to a station in this track
     * @param station: pointer to the station you want to disable a trackNode for
     * @return true if the operation was succesful
     */
    bool disableNodeForStation(Station* station);

    /**
     * @brief creates a string representation of the complete track (with all TrackNodes)
     * @return the string representation of the track
     */
    std::string getAsString() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};