//
// Created by Rob Mandelings on 17/04/2020.
//

#include <sstream>

#include "SimulationTime.h"
#include "Timer.h"
#include "constants.h"
#include "library.h"

SimulationTime::SimulationTime(int startHours, int startMinutes, int startSeconds) :
        m_simulationTimeStart(startHours * 60 * 60 * 1000 + startMinutes * 60 * 1000 + startSeconds * 1000) {
    SimulationTime::_initCheck = this;
    ENSURE(this->properlyInitialized(), "SimulationTime must be properly initialized to before its member variables are used.");
}

SimulationTime& SimulationTime::get() {
    static SimulationTime simulationTime(constants::SIMULATION_START_HOUR, constants::SIMULATION_START_MINUTE, constants::SIMULATION_START_SECOND);

    return simulationTime;
}

/** Stukje code om seconden om te zetten in uren, minuten en seconden: https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c */
std::string SimulationTime::getFormattedTime() const {
    REQUIRE(this->properlyInitialized(), "SimulationTime must be properly initialized to before its member variables are used.");
    double secondsOfDay = double((m_simulationTimeStart + Timer::get().getTimePassedMillis()) % (24 * 60 * 60 * 1000)) / 1000;

    int hours = (int) secondsOfDay / 3600;
    int remainder = (int) secondsOfDay - hours * 3600;
    int mins = remainder / 60;
    remainder = remainder - mins * 60;
    int secs = remainder;

    std::stringstream ss;

    ss << "[" << hours << ":" << (mins < 10 ? "0" : "") << mins << ":" << (secs < 10 ? "0" : "") << secs << "] ";

    return ss.str();
}

bool SimulationTime::properlyInitialized() const {
    return SimulationTime::_initCheck == this;
}
