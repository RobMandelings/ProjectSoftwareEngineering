//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METRONET_H
#define PROJECTSOFTWAREENGINEERING_METRONET_H

#include "library.h"
#include "Track.h"

class Station;

class Tram;

/**
 * Class containing settings and values of the complete MetroNet you want to simulate
 */
class MetroNet {
private:
    string m_name;
    vector<Tram*> m_trams;
    vector<Station*> m_stations;
    vector<Track*> m_tracks;

    MetroNet* _initCheck;
public:

    explicit MetroNet(const string& name);

    ~MetroNet();

    /**
     * @brief Simple getter
     * @return the name of this metronet
     */
    const string& getName() const;

    /**
     * @brief retrieves a tram from the list of trams corresponding to the given line
     * @param line: the line of the tram you want to retrieve
     * @return a pointer to the tram (NULL if no tram was found)
     */
    Tram* getTram(int line) const;

    /**
     * @brief retrieves a station from the list of stations corresponding with its name
     * @param line: the name of the station you want to retrieve
     * @return a pointer to the station (NULL if none found)
     */
    Station* getStation(const char* name) const;

    /**
     * Gets the track corresponding to the given line
     * @param line: the line you want to get the track for
     * @return the track
     */
    Track* getTrack(int line);

    /**
     * @brief Simple getter
     * @return all trams present in this metronet
     */
    const vector<Tram*>& getTrams() const;

    /**
     * @brief Simple getter
     * @return all stations present in this metronet
     */
    const vector<Station*>& getStations() const;

    /**
     * @return all tracks present in this metronet
     */
    const vector<Track*>& getTracks() const;

    /**
     * @brief adds a station to this MetroNet
     * @param station: a pointer to the station you want to add
     */
    void addStation(Station* station);

    /**
     * @brief adds a tram to this MetroNet
     * @param station: a pointer to the tram you want to add
     */
    void addTram(Tram* tram);

    /**
     * @brief adds a track to this MetroNet
     * @param station: a pointer to the track you want to add
     */
    void addTrack(Track* track);

    /**
     * @brief updates the location of all trams in this metronet
     */
    void updateTramLocations();

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};

#endif //PROJECTSOFTWAREENGINEERING_METRONET_H
