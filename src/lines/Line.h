//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once

#include <string>
#include "LineNode.h"
#include "library.h"

class Tram;

class Line {

private:

    /** The line number (index, used for identification of the different lines) of this line */
    int m_lineNumber;

    /** The access node of the line */
    LineNode* m_firstNode;

    Line* _initCheck;
    
public:

    /**
     * @brief simple constructor
     * @param line: the line this line is on
     * @param firstNode: the 'entry' node of this line (entry to the linked list of LineNodes)
     *
     \n ENSURE(m_line>=0,"Line must be a positive number.");
     \n ENSURE(m_firstNode!=NULL && m_firstNode->properlyInitialized(), "The first node cannot be NULL.");
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Line(int line, LineNode* firstNode);

    /**
     * @brief simple constructor
     *
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Line();

    /**
     * @brief simple destructor
     */
    ~Line();

    /**
     * @brief Checks to see if this line is only going through metronets (makes it completely underground)
     * @return true if the metronet is competely underground, false if not
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(m_firstNode != NULL, "The first node of this line cannot be null");
     */
    bool completelyUnderground() const;

    /**
     * @brief simple setter
     * @param line: the newLine of this line
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     \n ENSURE(m_lineNumber == line, "m_line must be set to line.");
     */
    void setLineNumber(int line);

    /**
     * @brief simple getter
     * @return the line of this line
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(m_line>=0, "Line cannot be a negative number.");
     \n ENSURE(m_line==line,"m_line must be set to line.");
     */
    int getLineNumber() const;

    /**
     * @brief simple getter
     * @return the first node / entry node of this line
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(m_firstNode!=NULL && m_firstNode->properlyInitialized(), "The first node cannot be NULL.");
     */
    LineNode* getFirstNode() const;

    /**
     * @brief gets the corresponding LineNode for a given station in this line
     * @param station: pointer to the station you want to get the node for
     * @return: the corresponding line node
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(station!=NULL && station->properlyInitialized(), "Station cannot be NULL.");
     \n ENSURE(lineNode!=NULL && lineNode->properlyInitialized(),"The line node cannot be NULL.");
     */
    LineNode* getNodeForStation(Station* station);

    /**
     * Inserts a node as the last element of the line
     * @param lineNode the node you want to add to the line
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(lineNode!=NULL && lineNode->properlyInitialized(), "A line node cannot be NULL.");
     \n ENSURE(m_firstNode!=NULL && m_firstNode->properlyInitialized(), "After an insert, the first node cannot be NULL.");
     \n ENSURE(this->getAsVector().size() > oldSize, "A node must be added after insertNode is called.");
     */
    void insertNode(LineNode* lineNode);

    /**
     * @brief disables the LineNode corresponding to a station in this line
     * @param station: pointer to the station you want to disable a lineNode for
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(station!=NULL && station->properlyInitialized(), "Station cannot be NULL.");
     \n ENSURE(lineNode->isUnderConstruction(),"The line node must be under construction.");
     */
    void disableNodeForStation(Station* station);

    /**
     * @return the line in vector representation (not circular)
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     \n REQUIRE(m_firstNode != NULL, "The first node of this line cannot be null");
     */
    std::vector<LineNode*> getAsVector() const;

    /**
     * @brief creates a string representation of the complete line (with all LineNodes)
     * @return the string representation of the line
     *
     \n REQUIRE(this->properlyInitialized(), "Line must be initialized before its member variables are used.");
     */
    std::string getAsString() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;
};