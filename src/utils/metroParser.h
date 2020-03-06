//
// Created by Rob Mandelings on 6/03/2020.
//

#pragma once

#include "../library.h"
#include "tinyxml.h"
#include "../MetroNet.h"

/** Utility file specific for parsing xml files into MetroNet objects */
namespace metroParser {

    /**
     * @brief Parses an XML file into a MetroNet object
     * @param filename the path to a .xml file
     * @return a MetroNet object containing the different stations, trams and their connections
     */
    MetroNet* parseMetroNetXml(const char* filename);

};


