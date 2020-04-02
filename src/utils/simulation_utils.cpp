//
// Created by thibaultpoels on 17/03/2020.
//

#include "simulation_utils.h"

namespace simulation_utils{
    void simulateTrams(MetroNet& metroNet, int MAXTIME, bool debug) {

        std::ofstream out("../output/events.metro", std::ofstream::trunc);
        out.close();

        if(!debug) std::cout << "Simulating trams..." << std::endl;
        while (MAXTIME > 0) {

            metroNet.updateTramLocations();
            if(!debug) std::cout << "Updated tram locations " << std::endl;
            MAXTIME--;
            usleep(1);
        }
    }
}
