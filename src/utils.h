//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_UTILS_H
#define PROJECTSOFTWAREENGINEERING_UTILS_H

#include "library.h"
#include "tinyxml.h"

class MetroNet;

namespace utils {
    MetroNet* parseMetroNet(const char* filename);
}

#endif //PROJECTSOFTWAREENGINEERING_UTILS_H
