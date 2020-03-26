//
// Created by Rob Mandelings on 6/03/2020.
//

#pragma once

#include "../library.h"
#include "tinyxml.h"
#include "../MetroNet.h"

/** Utility file specific for parsing xml files into MetroNet objects */
namespace metro_parser {

    class MetroNetParseException : public std::exception {
    public:
        const char* what() const throw();
    };

    /**
     * @brief Parses an XML file into a MetroNet object
     * @param filename the path to a .xml file
     * @throws MetroNetParseException
     * @return a MetroNet object containing the different stations, trams and their connections
     */
    MetroNet* parseMetroNetXml(const string& filename, bool debug=false);

};