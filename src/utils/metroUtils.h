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

    /**
     * @brief converts a string into an integer
     * @param input: the input string you want to convert to an integer
     * @return the converted value
     */
    int stoi(const string& input);

    /**
     * @brief Creates a file containing the current situation of the metronet given
     * @param metroNet: the metronet you want to create a file for
     * @param outputFilename: the location and name of the file
     */
    void printMetroNet(MetroNet* metroNet, const char* outputFilename);

}

#endif //PROJECTSOFTWAREENGINEERING_METROUTILS_H
