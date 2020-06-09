//
// Created by Rob Mandelings on 6/03/2020.
//

#pragma once

#include "../library.h"
#include "tinyxml.h"
#include "../MetroNet.h"

/** Utility file specific for parsing xml files into MetroNet objects */
namespace metro_parser {

    /**
     * @brief a metro parse exception is thrown is something went wrong whilst parsing an xml file
     */

    class MetroNetException : public std::exception {
    public:
        virtual const char* what() const throw()=0;
    };
    
    class FileException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class ExistingTrackException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class EqualSourceAndDestinationOnTrackException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NegativePlatformNumberException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NoPlatformsForStationException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class ExistingPlatformException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class AmountOfPlatformsException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class StationTypeException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NegativeLineNumberException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class XMLSyntaxException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class StationNotFoundException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class SingleNodeLineException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class MissingAttributeException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NegativeVehicleNumberException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class LineNodeNotFoundException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class LineNotFoundException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class PlatformNotFoundException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class TramTypeException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class PlatformPropertyException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NegativeQueueSizeForTrackException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    class NegativeSpeedException : public MetroNetException {
    public:
        const char* what() const throw();
    };

    /**
     * @brief Parses an XML file into a MetroNet object
     * @param filename the path to a .xml file
     * @throws MetroNetParseException
     * @return a MetroNet object containing the different stations, trams and their connections
     */
    MetroNet* parseMetroNetXml(const string& filename, bool debug = false);

};