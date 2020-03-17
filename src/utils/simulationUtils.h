//
// Created by thibaultpoels on 17/03/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_SIMULATIONUTILS_H
#define PROJECTSOFTWAREENGINEERING_SIMULATIONUTILS_H

#include "../library.h"
#include "../MetroNet.h"

namespace simulation{
    void simulateTrams(MetroNet& metroNet, int MAXTIME, bool debug = false);
}

#endif //PROJECTSOFTWAREENGINEERING_SIMULATIONUTILS_H
