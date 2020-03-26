//
// Created by thibaultpoels on 17/03/2020.
//

#include "simulation_utils.h"

namespace simulation_utils{
    void simulateTrams(MetroNet& metroNet, int MAXTIME, bool debug) {

        std::ofstream out("../output/events.metro", std::ofstream::trunc);
        out.close();

        if(!debug) cout << "Simulating trams..." << endl;
        while (MAXTIME > 0) {

            metroNet.updateTramLocations();
            if(!debug) cout << "Updated tram locations " << endl;
            MAXTIME--;
            usleep(1);
        }
    }
}
