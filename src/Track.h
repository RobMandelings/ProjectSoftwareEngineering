//
// Created by Rob Mandelings on 7/04/2020.
//

#pragma once

#include <queue>

class SpeedSignal;
class StopSignal;

class Tram;

class Platform;

class Track {

private:

    // TODO maybe add a length (which is calculated from the destinationStation and ?

    SpeedSignal* m_speedSignal;

    StopSignal* m_stopSignal;

    /** The source platform of this track (where the track starts) */
    Platform* m_sourcePlatform;

    /** The destination platform of this track (where the track ends) */
    Platform* m_destinationPlatform;

    /** The trams which are currently waiting to enter the destination platform */
    std::queue<Tram*> m_waitingTrams;

    /** Amount of trams driving on the track */
    unsigned int m_amountOfTrams;

    Track* _initCheck;

public:

    /** @brief simple constructor
     * @param sourcePlatform The source platform of this track (where the track starts)
     * @param destinationPlatform The destination platform of this track (where the track ends)
     */
    Track(Platform* sourcePlatform, Platform* destinationPlatform);

    /**
     * @brief simple getter
     * @return the source platform of this track
     */
    Platform* getSourcePlatform() const;

    /**
     * @brief simple getter
     * @return the destination platform of this track
     */
    Platform* getDestinationPlatform() const;

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

    void addTram();

    void deleteTram();

    SpeedSignal* getSpeedSignal() const;

    StopSignal* getStopSignal() const;

    void setSpeedSignal(SpeedSignal* speedSignal);

    void setStopSignal(StopSignal* stopSignal);

    bool hasSpace() const;

    int getAmountOfTrams() const;

    bool properlyInitialized() const;

};