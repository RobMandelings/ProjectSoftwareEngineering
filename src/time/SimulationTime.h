//
// Created by Rob Mandelings on 17/04/2020.
//

#pragma once

#include <string>

/** Class used to represent realistic time in the output (e.g. [12:00:00]) */
class SimulationTime {

private:

    SimulationTime(int startHours, int startMinutes, int startSeconds);

    long m_simulationTimeStart;

public:

    static SimulationTime& get();

    std::string getFormattedTime() const;

};