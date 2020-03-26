//
// Created by thibaultpoels on 17/03/2020.
//

#include "simulation_utils.h"
#include "constants.h"
#include "clog.h"

namespace simulation_utils{
    void simulateTrams(MetroNet& metroNet, int MAXTIME, bool debug) {

        std::ofstream out("../output/events.metro", std::ofstream::trunc);
        out.close();

        if(!debug) clog_info(CLOG(constants::LOGGER_ID), "Simulating trams...");
        while (MAXTIME > 0) {

            metroNet.updateTramLocations();
            if(!debug) clog_info(CLOG(constants::LOGGER_ID), "Updated tram locations ");
            MAXTIME--;
            usleep(1);
        }
    }
}
