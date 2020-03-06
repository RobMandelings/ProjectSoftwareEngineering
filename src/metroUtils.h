//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METROUTILS_H
#define PROJECTSOFTWAREENGINEERING_METROUTILS_H

#include "library.h"
#include "tinyxml.h"


class MetroNet;

/** Basic utility file containing various useful functions */
namespace metroUtils {

    /**
     * @brief Parses an XML file into a MetroNet object
     * @param filename the path to a .xml file
     * @return a MetroNet object containing the different stations, trams and their connections
     */
    MetroNet* parseMetroNetXml(const char* filename);
}

#endif //PROJECTSOFTWAREENGINEERING_METROUTILS_H
