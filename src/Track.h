//
// Created by Rob Mandelings on 7/04/2020.
//

#pragma once

#include <queue>

class Tram;

class Station;

class Track {

private:

    // TODO maybe add a length (which is calculated from the destinationStation and ?

    /** The source station of this track (where the track starts) */
    Station* m_sourceStation;

    /** The destination station of this track (where the track ends) */
    Station* m_destinationStation;

    /** The trams which are currently waiting to enter the destination station */
    std::queue<Tram*> m_waitingTrams;

public:

    /** @brief simple constructor
     * @param sourceStation The source station of this track (where the track starts)
     * @param destinationStation The destination station of this track (where the track ends)
     */
    Track(Station* sourceStation, Station* destinationStation);

    /**
     * @brief simple getter
     * @return the source station of this track
     */
    Station* getSourceStation() const;

    /**
     * @brief simple getter
     * @return the destination station of this track
     */
    Station* getDestinationStation() const;

    /**
     * @brief simple getter
     * @return the trams currently riding on this track
     */
    std::queue<Tram*> getWaitingTrams() const;

    Tram* getFirstTramInLine() const;

    /**
     * @brief adds a tram to the trams currently riding on this tram (should be used by tram->updateLocation())
     * @param tram the tram to add to the track
     */
    void addWaitingTram(Tram* tram);

};