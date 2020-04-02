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
     *
     \n ENSURE(line>=0,"Line must be a positive number.");
     \n ENSURE(firstNode->properlyInitialized(), "The first node cannot be NULL.");
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Track(int line, TrackNode* firstNode);

    /**
     * @brief simple constructor
     *
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Track();

    ~Track();

    /**
     * @brief simple setter
     * @param line: the newLine of this track
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     */
    void setLine(int line);

    /**
     * @brief simple getter
     * @return the line of this track
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    int getLine() const;

    /**
     * @brief simple getter
     * @return the first node / entry node of this track
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n ENSURE(m_firstNode!=NULL, "The first node cannot be NULL.");
     */
    TrackNode* getFirstNode() const;

    /**
     * @brief gets the corresponding TrackNode for a given station in this track
     * @param station: pointer to the station you want to get the node for
     * @return: the corresponding track node
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(station->properlyInitialized(), "Station cannot be NULL.");
     \n ENSURE(trackNode->properlyInitialized(),"The track node cannot be NULL.");
     */
    TrackNode* getNodeForStation(Station* station);

    /**
     * Inserts a node as the last element of the track
     * @param trackNode the node you want to add to the track
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(trackNode!=NULL, "A track node cannot be NULL.");
     \n ENSURE(m_firstNode!=NULL, "After an insert, the first node cannot be NULL.");
     */
    void insertNode(TrackNode* trackNode);

    /**
     * @brief disables the TrackNode corresponding to a station in this track
     * @param station: pointer to the station you want to disable a trackNode for
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(station->properlyInitialized(), "Station cannot be NULL.");
     \n ENSURE(trackNode->isUnderConstruction(),"The track node must be under construction.");
     */
    void disableNodeForStation(Station* station);

    /**
     * @brief creates a string representation of the complete track (with all TrackNodes)
     * @return the string representation of the track
     *
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    std::string getAsString() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};