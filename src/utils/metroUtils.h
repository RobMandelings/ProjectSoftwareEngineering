//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METROUTILS_H
#define PROJECTSOFTWAREENGINEERING_METROUTILS_H

#include "../library.h"
#include "tinyxml.h"


class MetroNet;

/** Common utility file containing various useful functions */
namespace metroUtils {

    int stoi(const string& input);

    void printMetroNet(MetroNet* metroNet);

}

#endif //PROJECTSOFTWAREENGINEERING_METROUTILS_H
