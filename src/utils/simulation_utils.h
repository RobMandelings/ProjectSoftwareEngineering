//
// Created by thibaultpoels on 17/03/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_SIMULATION_UTILS_H
#define PROJECTSOFTWAREENGINEERING_SIMULATION_UTILS_H

#include "../library.h"
#include "../MetroNet.h"

namespace simulation_utils {
    void simulateTrams(MetroNet& metroNet, int MAXTIME, bool debug = false);
}

#endif //PROJECTSOFTWAREENGINEERING_SIMULATION_UTILS_H
