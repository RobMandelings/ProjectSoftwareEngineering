//
// Created by Rob Mandelings on 17/04/2020.
//

#pragma once

#include <string>

/** Class used to represent realistic time in the output (e.g. [12:00:00]) */
class SimulationTime {

private:

    /**
     * @param startHour: the hour this simulation should start
     * @param startMinute: the minute this simulation should start
     * @param startSecond: the second this simulation should start
     */
    SimulationTime(int startHour, int startMinute, int startSecond);

    /**
     * The time the simulation starts, in milli seconds
     */
    long m_simulationTimeStart;

    SimulationTime* _initCheck;

public:

    /**
     * @return the instance of the SimulationTime object
     */
    static SimulationTime& get();

    long getSimulationTimeStart() const;

    /**
     * @return the current time in the simulation, format: [HH:MM:SS]
     \n REQUIRE(this->properlyInitialized(), "SimulationTime must be properly initialized to before its member variables are used.");
     */
    std::string getFormattedTime() const;
    
    static std::string getFormattedTime(long currentSimulationTime);

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};