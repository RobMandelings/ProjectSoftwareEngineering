//
// Created by thibaultpoels on 17/03/2020.
//

#include <ctime>

#include "simulation_utils.h"
#include "Timer.h"
#include "constants.h"
#include <cstdlib>
#include <sys/timeb.h>
#include <statistics/Statistics.h>
#include <cstring>
#include "SimulationTime.h"
#include "FileHandler.h"

namespace simulation_utils {
    
    bool simulateTrams(MetroNet& metroNet, vector<long>& returnTimes, bool debug) {
        
        if (!debug) std::cout << "Simulating trams..." << std::endl;
        int timeBefore = Timer::getCurrentTimeMillis();
        // FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Started the simulation" << std::endl;
        while (Timer::get().shouldRun()) {
            metroNet.updateTrams(debug);

            if (!debug) std::cout << "Current degree of occupancy: " << Statistics::get().getCurrentDegreeOfOccupancy() * 100 << "%" << std::endl;
            if (!debug) std::cout << "Revenue: " << Statistics::get().getTotalRevenue() << " euros" << std::endl;

            if (!debug) std::cout << "Updated tram locations " << std::endl;
            if (!returnTimes.empty()) {
                std::cout << "NOOOO " << SimulationTime::getFormattedTime(SimulationTime::get().getSimulationTimeStart() + returnTimes.at(0)) << std::endl;
                std::cout << "ANDERE " << SimulationTime::get().getFormattedTime() << std::endl;
                if (SimulationTime::getFormattedTime(SimulationTime::get().getSimulationTimeStart() + returnTimes.at(0)) == SimulationTime::get().getFormattedTime()) {
                    std::cout << "Should be" << std::endl;
                    returnTimes.erase(returnTimes.begin());
                    return true;
                }
            }
            Timer::get().setUpdateTime();
            usleep(1 / (float) constants::UPDATES_PER_SECOND * 1e6);
        }

        if (!debug) std::cout << "program ran for " << ((double) Timer::getCurrentTimeMillis() - timeBefore) / 1000 << " seconds" << std::endl;
        FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Ended the simulation" << std::endl;
        if (!debug) std::cout << "Simulation ended at: " << SimulationTime::get().getFormattedTime() << std::endl;
        if (!debug) std::cout << "With a final 'degree of occupancy' of " << Statistics::get().getCurrentDegreeOfOccupancy() * 100 << "% ";
        if (!debug) std::cout << "And revenue of " << Statistics::get().getTotalRevenue() << " euros" << std::endl;
        return false;
    }
}