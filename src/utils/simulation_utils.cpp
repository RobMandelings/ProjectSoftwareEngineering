//
// Created by thibaultpoels on 17/03/2020.
//

#include <ctime>

#include "simulation_utils.h"
#include "Timer.h"
#include "constants.h"
#include <cstdlib>
#include <sys/timeb.h>
#include "SimulationTime.h"
#include "FileHandler.h"

namespace simulation_utils {
    void simulateTrams(MetroNet& metroNet, bool debug) {

        if (!debug) std::cout << "Simulating trams..." << std::endl;
        int timeBefore = Timer::getCurrentTimeMillis();
        while (Timer::get().shouldRun()) {
            metroNet.updateTrams();

            if (!debug) std::cout << "Updated tram locations " << std::endl;
            Timer::get().setUpdateTime();
            usleep(1/(float) constants::UPDATES_PER_SECOND * 1e6);
        }

        std::cout << "program ran for " << ((double) Timer::getCurrentTimeMillis() - timeBefore) / 1000 << " seconds" << std::endl;
        std::cout << "Simulation time ended at: " << SimulationTime::get().getFormattedTime() << std::endl;
    }
}
