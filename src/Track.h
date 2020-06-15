//
// Created by Rob Mandelings on 7/04/2020.
//

#pragma once

#include <deque>
#include <fstream>

class SpeedSignal;

class StopSignal;

class Tram;

class Platform;

class Track {

private:

    // TODO maybe add a length (which is calculated from the destinationStation and ?

    /** The speed signal of this track, optional (NULL if none set) */
    SpeedSignal* m_speedSignal;

    /** The stop signal of this track, optional (NULL if none set) */
    StopSignal* m_stopSignal;

    /** The source platform of this track (where the track starts) */
    Platform* m_sourcePlatform;

    /** The destination platform of this track (where the track ends) */
    Platform* m_destinationPlatform;

    /** The trams which are currently waiting to enter the destination platform */
    std::deque<Tram*> m_waitingTrams;

    /** The tram currently riding on this track */
    Tram* m_ridingTram;

    Track* _initCheck;

public:

    /** @brief simple constructor
     * @param sourcePlatform The source platform of this track (where the track starts)
     * @param destinationPlatform The destination platform of this track (where the track ends)
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n ENSURE(m_sourcePlatform != NULL, "The source platform given cannot be NULL");
     \n ENSURE(m_destinationPlatform != NULL, "The destination platform given cannot be NULL");
     */
    Track(Platform* sourcePlatform, Platform* destinationPlatform);

    /**
     * @brief simple getter
     * @return the source platform of this track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(m_sourcePlatform, "sourceStation cannot be null!");
     */
    Platform* getSourcePlatform() const;

    /**
     * @brief simple getter
     * @return the destination platform of this track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(m_destionationPlatform, "destinationPlatform cannot be null!");
     */
    Platform* getDestinationPlatform() const;

    /**
     * @brief simple getter
     * @return the trams currently riding on this track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(getStopSignal(), "This track does not have a stop signal and thus cannot have a waiting list");
     \n REQUIRE(m_waitingTrams.size() <= getStopSignal()->getMaxAmountOfTrams(), "The amount of trams in m_waitingTrams is greater than the allowed maximum");
     */
    std::deque<Tram*>& getWaitingTrams();

    /**
     * @brief adds a tram to the trams currently riding on this tram (should be used by tram->updateLocation())
     * @param tram the tram to add to the track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(tram != NULL, "The tram given may not be NULL");
     \n REQUIRE(m_stopSignal, "Cannot add waiting tram: this track doesn't have a stopsignal");
     \n REQUIRE(!tramCapacityReached(), "Cannot add waiting tram: the tram capacity is already reached");
     \n ENSURE(m_waitingTrams.size()>oldSize, "A waiting tram must be added after addWaitingTram is called.");
     */
    void addWaitingTram(Tram* tram);

    /**
     * @brief simple getter
     * @return the speed signal of this track, NULL if none set
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    SpeedSignal* getSpeedSignal() const;

    /**
     * @brief simple getter
     * @return the stop signal of this track, NULL if none set
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    StopSignal* getStopSignal() const;

    /**
     * @brief sets the speed signal of this
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(speedSignal != NULL, "The speed signal given is NULL, can only set variable to non-NULL values")
     \n REQUIRE(m_speedSignal == NULL , "The speedsignal is already set!");
     \n ENSURE(m_speedSignal == speedSignal, "The speed signal must be properly set to its parameter.");
     */
    void setSpeedSignal(SpeedSignal* speedSignal);

    /**
     * @brief sets the speed signal of this
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     \n REQUIRE(stopSignal != NULL, "The stopSignal given is NULL, can only set variable to non-NULL values")
     \n REQUIRE(m_stopSignal == NULL , "The stopSignal is already set!");
     \n ENSURE(m_stopSignal == stopSignal, "The stop signal must be properly set to its parameter.");
     */
    void setStopSignal(StopSignal* stopSignal);

    /**
     * @brief tram capacity is reached if there is no stopsignal and already a tram riding on the track or it has a stopsignal and used the buffer settings
     * @return true if the tram capacity is reached
    \n REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    \n REQUIRE(m_stopSignal, "This track does not have a stop signal. The function tramcapacityReached() should not be called");
    \n REQUIRE(((int) m_waitingTrams.size() + (hasRidingTram() ? 1 : 0)) <= m_stopSignal->getMaxAmountOfTrams(), "There are more trams than this track can hold in the queue!")
     */
    bool tramCapacityReached() const;

    /**
     * @brief simple getter
     * @return if there currently is a tram riding on the track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    bool hasRidingTram() const;

    /**
     * @brief simple setting
     * @param ridingTram: the riding tram put on this track
    \n REQUIRE(this->properlyInitialized(), "Track must be properly initialized before its member methods are used.");
    \n REQUIRE(!m_ridingTram, "A tram is already riding on this track!");
    \n REQUIRE(!m_stopSignal || !tramCapacityReached(), "The tram capacity on this track is already reached! Cannot set the riding tram");
     */
    void setRidingTram(Tram* ridingTram);

    /**
     * @brief removes the riding tram from this track
     \n REQUIRE(this->properlyInitialized(), "Track must be initialized before its member variables are used.");
     */
    void removeTram();

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};

std::ostream& operator<<(std::ostream& os, Track& track);

std::ostream& operator<<(std::ostream& os, Track* track);