//
// Created by thibaultpoels on 27/02/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_METRO_UTILS_H
#define PROJECTSOFTWAREENGINEERING_METRO_UTILS_H

#include "../library.h"
#include "tinyxml.h"

class MetroNet;

/** Common utility file containing various useful functions */
namespace metro_utils {

    /**
     * @brief converts a string into an integer
     * @param input: the input string you want to convert to an integer
     * @return the converted value
     */
    int stoi(const string& input);

    /**
     * @brief converts a string into a double
     * @param input: the input string you want to convert to a double
     * @return the converted value
     */
    double stod(const string& input);

    /**
     * @brief Creates a file containing the current situation of the metronet given
     * @param metroNet: the metronet you want to create a file for
     * @param outputFilename: the location and name of the file
     */
    void printMetroNet(MetroNet* metroNet, const char* outputFilename);

    void grahicalImpression(const char* inputfile, const char* outputFilename);

}

#endif //PROJECTSOFTWAREENGINEERING_METRO_UTILS_H
