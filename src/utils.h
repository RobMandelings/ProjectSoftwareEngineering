//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_UTILS_H
#define PROJECTSOFTWAREENGINEERING_UTILS_H

#include "library.h"
#include "tinyxml.h"


class MetroNet;

/** Basic utility file containing various useful functions */
namespace utils {

    /**
     * @brief Parses an XML file into a MetroNet object
     * @param filename the path to a .xml file
     * @return a MetroNet object containing the different stations, trams and their connections
     */
    MetroNet* parseMetroNetXml(const char* filename);
}

#endif //PROJECTSOFTWAREENGINEERING_UTILS_H
