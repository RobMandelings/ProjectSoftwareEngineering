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
#include "SimulationTime.h"
#include "FileHandler.h"

namespace simulation_utils {
    void simulateTrams(MetroNet& metroNet, bool debug) {

        if (!debug) std::cout << "Simulating trams..." << std::endl;
        int timeBefore = Timer::getCurrentTimeMillis();
        FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Started the simulation" << std::endl;
        while (Timer::get().shouldRun()) {
            metroNet.updateTrams(debug);

            std::cout << Statistics::get().getCurrentDegreeOfOccupancy() << std::endl;
            std::cout << Statistics::get().getTotalRevenue() << std::endl;

            if (!debug) std::cout << "Updated tram locations " << std::endl;
            Timer::get().setUpdateTime();
            usleep(1 / (float) constants::UPDATES_PER_SECOND * 1e6);
        }

        if (!debug) std::cout << "program ran for " << ((double) Timer::getCurrentTimeMillis() - timeBefore) / 1000 << " seconds" << std::endl;
        FileHandler::get().getOfstream() << SimulationTime::get().getFormattedTime() << "Ended the simulation" << std::endl;
        if (!debug) std::cout << "Simulation ended at: " << SimulationTime::get().getFormattedTime() << std::endl;
    }
}