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

    class MetroNetParseException : public std::exception {
    public:
        virtual const char* what() const throw()=0;
    };
    
    class FileException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class ExistingTrackException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class EqualSourceAndDestinationOnTrackException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NegativePlatformNumberException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NoPlatformsForStationException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NoNameGivenForStationException : public MetroNetParseException {
        const char* what() const throw();
    };

    class NoNameGivenForMetroNetException : public MetroNetParseException {
        const char* what() const throw();
    };

    class ExistingPlatformException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class AmountOfPlatformsException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class StationTypeException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NegativeLineNumberException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class XMLSyntaxException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class StationNotFoundException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class SingleNodeLineException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class MissingAttributeException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NegativeVehicleNumberException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class LineNodeNotFoundException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class LineNotFoundException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class PlatformNotFoundException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class TramTypeException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class PlatformPropertyException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NegativeQueueSizeForTrackException : public MetroNetParseException {
    public:
        const char* what() const throw();
    };

    class NegativeSpeedException : public MetroNetParseException {
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