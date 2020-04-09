//
// Created by jasper on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATION_H
#define PROJECTSOFTWAREENGINEERING_STATION_H

#include "library.h"

class Line;
class Tram;

enum StationType {
    ABOVE_GROUND,
    UNDERGROUND
};

class Station {

private:
    string m_name;
    vector<Line*> m_lines;

    Station* _initCheck;

    Tram* m_tram;

public:

    /**
     \n REQUIRE(this->properlyInitialized(), "Constructor must end ...");
     */
    Station();

    virtual ~Station();

    void setTram(Tram* tram);

    Tram* getTram() const;

    bool hasTram() const;

    /**
     * @return station type
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     */
    virtual StationType getType() const = 0;

    /**
     * @brief Simple getter
     * @return the name of this station
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n ENSURE(m_name.length()>0,"Name can't be the empty string.");
     */
    const string& getName() const;

    /**
     * @brief sets the name of this station
     * @param name: the name you want to set this station to
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(name.length()>0,"Name can't be the empty string.");
     */
    void setName(const string& name);

    /**
     * @brief gets a line corresponding to the line given
     * @return the line
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     \n ENSURE(m_name==name,"m_name has to be set to name.");
     */
    Line* getLine(int line);

    /**
     * @brief adds a line to the list of lines in this station
     *
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(line->properlyInitialized(), "Line cannot be NULL.");
     */
    void addLine(Line* line);

    /**
     * @brief checks if this object was properly initialized
     \n REQUIRE(this->properlyInitialized(), "Station must be initialized before its member variables are used.");
     \n REQUIRE(line!=NULL && line->properlyInitialized(), "Line cannot be NULL.");
     */
    bool properlyInitialized() const;
};


#endif //PROJECTSOFTWAREENGINEERING_STATION_H
