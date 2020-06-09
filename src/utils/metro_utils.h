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
     * Creates a list of return times (in milliseconds, relative to the current time) for the program
     * @param returnTimes: the returnTimes in seconds (after how many seconds the simulation should be returned)
     */
    std::vector<long> createReturnTimes(const std::vector<int>& returnTimes);

    /**
     * @brief converts a string into an integer
     * @param input: the input string you want to convert to an integer
     * @return the converted value
     */
    int stoi(const string& input);

    /**
     * @brief converts an integer into a string
     * @param input: the input integer you want to convert to a string
     * @return the converted value
     */
    string itos(const int input);

    /**
     * @brief converts a char into a string
     * @param input: the input char you want to convert to a string
     * @return the converted value
     */
    string ctos(const char c);

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

    /**
     * @brief Creates a new file which contains the final situation of the metronet using a graphical impression
     * @param inputfile: the inputfile is the normal outputfile which gets created by the "printMetroNet" method
     * @param outputFilename: location and name of the file
     */
    void getGraphicalImpression(const char* inputfile, const char* outputFilename);

}

#endif //PROJECTSOFTWAREENGINEERING_METRO_UTILS_H
