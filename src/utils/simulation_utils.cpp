//
// Created by thibaultpoels on 17/03/2020.
//

#include "simulation_utils.h"
#include "Timer.h"
#include "constants.h"

namespace simulation_utils {
    void simulateTrams(MetroNet& metroNet, bool debug) {

        std::ofstream out("../output/events.metro", std::ofstream::trunc);
        out.close();

        if (!debug) std::cout << "Simulating trams..." << std::endl;
        while (Timer::get().programRunTime()) {

            Timer::get().setUpdateTime();

            metroNet.updateTramLocations();
            if (!debug) std::cout << "Updated tram locations " << std::endl;
            usleep(1/constants::UPDATES_PER_SECOND);
        }
    }
}
