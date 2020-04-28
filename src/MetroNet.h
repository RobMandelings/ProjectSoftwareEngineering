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

    /** The name of this metronet (e.g. 'Antwerpen') */
    string m_name;

    /** All the trams in this metronet */
    vector<Tram*> m_trams;

    /** All the trams in this metronet */
    vector<Station*> m_stations;

    /** All the lines in this metronet */
    vector<Line*> m_lines;

    /** All the tracks in this metronet */
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
     * @brief retrieves a station from the list of stations corresponding with its name
     * @param line: the name of the station you want to retrieve
     * @return a pointer to the station (NULL if none found)
     *
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     \n REQUIRE(name!=NULL,"Name cannot be empty.");
     */
    Station* getStation(const char* name) const;

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

    /**
     * @brief a track has trams which only go in one direction, so a track has a source and destination
     * @param sourcePlatform: where the track starts
     * @param destinationPlatform: where the track ends
     * @return a track which is connected by the source platform and the destination platform, NULL if none exists
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    Track* getTrack(Platform* sourcePlatform, Platform* destinationPlatform);

    /**
     * @brief checks if a track exists within the metronet which has the specified source- and destination platform
     * @param sourcePlatform: where the track starts
     * @param destinationPlatform: where the track ends
     * @return true if the track exists within the metronet, false if not
     \n REQUIRE(this->properlyInitialized(), "MetroNet must be initialized before its member variables are used.");
     */
    bool hasTrack(Platform* sourcePlatform, Platform* destinationPlatform);

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
    void updateTrams(bool debug);

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
