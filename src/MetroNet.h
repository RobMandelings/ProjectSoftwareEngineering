//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METRONET_H
#define PROJECTSOFTWAREENGINEERING_METRONET_H

#include "library.h"
#include "lines/Line.h"

class Station;

class Tram;

class Track;

class Platform;

/**
 * Class containing settings and values of the complete MetroNet you want to simulate
 */
class MetroNet {
private:
    string m_name;
    vector<Tram*> m_trams;
    vector<Station*> m_stations;
    vector<Line*> m_lines;
    vector<Track*> m_tracks;

    MetroNet* _initCheck;
public:

    /**
     * @brief simple constructor of MetroNet
     * @param name: name of MetroNet
     *
     \n ENSURE(m_name.length()>0, "Name can't be the empty string.");
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */

    explicit MetroNet(const string& name);

    ~MetroNet();

    /**
     * @brief Simple getter
     * @return the name of this metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(m_name.length()>0,"Name can't be the empty string.");
     */
    const string& getName() const;

    /**
     * @brief retrieves a tram from the list of trams corresponding to the given line
     * @param line: the line of the tram you want to retrieve
     * @return a pointer to the tram (NULL if no tram was found)
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     */
    Tram* getTram(int line) const;

    /**
     * @brief retrieves a station from the list of stations corresponding with its name
     * @param line: the name of the station you want to retrieve
     * @return a pointer to the station (NULL if none found)
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(name!=NULL,"Name cannot be empty.");
     */
    Station* getStation(const char* name) const;

    Platform* getPlatform(const char* name, int platformNumber, Direction direction) const;

    /**
     * Gets the line corresponding to the given line
     * @param line: the line you want to get the line for
     * @return the line
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(line>=0,"Line must be a positive number.");
     */
    Line* getLine(int line);

    /**
     * @brief Simple getter
     * @return all trams present in this metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    const vector<Tram*>& getTrams() const;

    /**
     * @brief Simple getter
     * @return all stations present in this metronet
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    const vector<Station*>& getStations() const;

    /**
     * @return all lines present in this metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    const vector<Line*>& getLines() const;

    /**
     * @return all tracks present in this metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    const vector<Track*>& getTracks() const;

    bool trackExists(Platform* sourcePlatform, Platform* destinationPlatform);

    /**
     * @brief adds a station to this MetroNet
     * @param station: a pointer to the station you want to add
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(station!=NULL && station->properlyInitialized(), "Station cannot be NULL.");
     */
    void addStation(Station* station);

    /**
     * @brief adds a tram to this MetroNet
     * @param station: a pointer to the tram you want to add
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(tram!=NULL && tram->properlyInitialized(),"Tram cannot be NULL.");
     */
    void addTram(Tram* tram);

    /**
     * @brief adds a line to this MetroNet
     * @param station: a pointer to the line you want to add
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(line!=NULL && line->properlyInitialized(), "Line cannot be NULL.");
     \n REQUIRE(this->checkVehicleNumberAvailability(tram), "Tram number must be available in this line.");
     */
    void addLine(Line* line);

    /**
     * @brief adds a track to this MetroNet
     * @param station: a pointer to the track you want to add
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(tram!=NULL && tram->properlyInitialized(),"Track cannot be NULL.");
     */
    void addTrack(Track* track);

    /**
     * @brief updates the location of all trams in this metronet
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    void updateTramLocations();

    /**
     * @brief checks whether a certain vehicle number is still available in a certain line
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */

    bool checkVehicleNumberAvailability(Tram* tram);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};

#endif //PROJECTSOFTWAREENGINEERING_METRONET_H
