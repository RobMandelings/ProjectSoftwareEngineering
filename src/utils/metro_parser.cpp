//
// Created by Rob Mandelings on 6/03/2020.
//

#include <statistics/Statistics.h>
#include "metro_parser.h"
#include "../MetroNet.h"
#include "../trams/Tram.h"
#include "lines/Line.h"
#include "lines/LineNode.h"
#include "metro_utils.h"
#include "DesignByContract.h"
#include "Albatros.h"
#include "PCC.h"
#include "Station.h"
#include "MetroStation.h"
#include "TramStop.h"
#include "Track.h"
#include "constants.h"
#include "Signal.h"
#include "StopSignal.h"
#include "SpeedSignal.h"

// TODO custom metronet parse exception messages
namespace metro_parser {

    namespace {

        void addTrackBetweenPlatforms(MetroNet* metroNet, Platform* sourcePlatform, Platform* destinationPlatform, bool debug) {

            if (sourcePlatform->getStation() != destinationPlatform->getStation()) {
                if (sourcePlatform != destinationPlatform) {
                    if (!metroNet->hasTrack(sourcePlatform, destinationPlatform)) {
                        Track* track = new Track(sourcePlatform, destinationPlatform);
                        sourcePlatform->addOutgoingTrack(track);
                        destinationPlatform->addIncomingTrack(track);
                        metroNet->addTrack(track);

                    } else {
                        if (!debug)
                            std::cerr << "track with source platform 'station " << sourcePlatform->getStation()->getName() << ", number " << sourcePlatform->getNumber() << "'"
                                      << " and destination platform 'station " << destinationPlatform->getStation()->getName() << ", number " << destinationPlatform->getNumber()
                                      << "' already exists in the metronet" << std::endl;
                        throw ExistingTrackException();
                    }
                } else {
                    if (!debug)
                        std::cerr << "The destination of the track is equal to the source (station: " << sourcePlatform->getStation()->getName() << ", number: "
                                  << sourcePlatform->getNumber() << ")" << std::endl;
                    throw EqualSourceAndDestinationOnTrackException();
                }
            } else {
                if (!debug)
                    std::cerr << "Cannot add track between platforms: the source station and destination station are the same (" << sourcePlatform->getStation()->getName() << ")"
                              << std::endl;
                throw EqualSourceAndDestinationOnTrackException();
            }
        }

        Platform* parseNewPlatform(TiXmlElement* platformElement, bool debug) {
            int platformNumber = -1;
            for (TiXmlElement* currentPerronChildElement = platformElement->FirstChildElement();
                 currentPerronChildElement != NULL; currentPerronChildElement = currentPerronChildElement->NextSiblingElement()) {
                if (!strcmp(currentPerronChildElement->Value(), "nummer")) {
                    platformNumber = metro_utils::stoi(currentPerronChildElement->GetText());
                }
            }
            if (platformNumber < 0) {
                if (!debug) std::cerr << "The platform number cannot be negative" << std::endl;
                throw NegativePlatformNumberException();
            } else {
                return new Platform(platformNumber);
            }
        }

        void parseNewStation(MetroNet* metroNet, TiXmlElement* stationElement, bool debug) {

            string stationName;
            std::string stationType;
            std::vector<Platform*> platforms;

            for (TiXmlElement* stationChildElement = stationElement->FirstChildElement(); stationChildElement != NULL;
                 stationChildElement = stationChildElement->NextSiblingElement()) {
                string childElementName = stationChildElement->Value();
                if (childElementName == "naam") {
                    if(stationChildElement->GetText() != NULL){
                        stationName = stationChildElement->GetText();   
                    }
                } else if (childElementName == "type") {
                    stationType = stationChildElement->GetText();
                } else if (childElementName == "perron") {
                    Platform* platform = parseNewPlatform(stationChildElement, debug);
                    platforms.push_back(platform);
                }
            }

            if (stationName.empty()) {
                if (!debug) std::cerr << "No name was given for this station " << std::endl;
                throw NoNameGivenForStationException();
            }

            if (platforms.empty()) {
                if (!debug) std::cerr << "There are no platforms found for the current station " << stationName << std::endl;
                throw NoPlatformsForStationException();
            }

            Station* station = NULL;
            if (stationType == "MetroStation") {
                MetroStation* metroStation = new MetroStation();
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {

                    if (metroStation->getPlatform((*it)->getNumber()) == NULL) {
                        metroStation->addPlatform(*it);
                    } else {
                        if (!debug) std::cerr << "The platform with number " << (*it)->getNumber() << " already exists in the metrostation" << std::endl;
                        throw ExistingPlatformException();
                    }
                }
                station = metroStation;
                // The station of the platform is set to the currentStation
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); it++) {
                    (*it)->setStation(station);
                }
            } else if (stationType == "TramStop") {
                if (platforms.size() > 1) {
                    if (!debug) std::cerr << "A tram stop can only have 1 platform. Given: " << platforms.size() << std::endl;
                    throw AmountOfPlatformsException();
                } else {
                    station = new TramStop(platforms.at(0));
                    TramStop* tramStop = (TramStop*) station;
                    tramStop->getPlatformTo()->setStation(station);
                    tramStop->getPlatformFrom()->setStation(station);
                }
            } else {
                if (!debug) std::cerr << "The type of the station wasn't recognized" << stationType << std::endl;
                throw StationTypeException();
            }
            station->setName(stationName);

            metroNet->addStation(station);

        }

        void parseLine(MetroNet* metroNet, TiXmlElement* lineElement, bool debug) {
            Line* line = new Line();
            int lineNumber = metro_utils::stoi(lineElement->Attribute("nr"));
            if (lineNumber < 0) {
                throw NegativeLineNumberException();
            }
            line->setLineNumber(lineNumber);
            for (TiXmlElement* lineNodeElement = lineElement->FirstChildElement();
                 lineNodeElement != NULL; lineNodeElement = lineNodeElement->NextSiblingElement()) {
                if (!strcmp(lineNodeElement->Value(), "LIJNNODE")) {

                    Platform* platformHeen = NULL;
                    Platform* platformTerug = NULL;

                    for (TiXmlElement* stationElement = lineNodeElement->FirstChildElement();
                         stationElement != NULL; stationElement = stationElement->NextSiblingElement()) {

                        if (!strcmp(stationElement->Value(), "station")) {

                            Station* station = NULL;
                            std::string stationName;
                            int platformNumberHeen = -1;
                            int platformNumberTerug = -1;

                            for (TiXmlElement* stationChildElement = stationElement->FirstChildElement();
                                 stationChildElement != NULL; stationChildElement = stationChildElement->NextSiblingElement()) {

                                if (!strcmp(stationChildElement->Value(), "naam")) {
                                    station = metroNet->getStation(stationChildElement->GetText());
                                    stationName = stationChildElement->GetText();
                                } else if (!strcmp(stationChildElement->Value(), "heenperron")) {
                                    platformNumberHeen = metro_utils::stoi((stationChildElement->GetText()));
                                } else if (!strcmp(stationChildElement->Value(), "terugperron")) {
                                    platformNumberTerug = metro_utils::stoi((stationChildElement->GetText()));
                                } else {
                                    if (!debug) std::cerr << " unrecognized element '" << stationChildElement->Value() << "' within station" << std::endl;
                                    throw XMLSyntaxException();
                                }
                            }

                            if (platformNumberHeen < 0 || platformNumberTerug < 0) {
                                throw NegativePlatformNumberException();
                            }

                            if (station) {
                                station->addLine(line);
                                if (station->getType() == UNDERGROUND) {
                                    MetroStation* metroStation = (MetroStation*) station;
                                    platformHeen = metroStation->getPlatform(platformNumberHeen);
                                    platformTerug = metroStation->getPlatform(platformNumberTerug);
                                } else {
                                    TramStop* tramStop = (TramStop*) station;
                                    if (tramStop->getPlatformTo()->getNumber() == platformNumberHeen) {
                                        platformHeen = tramStop->getPlatformTo();
                                        // A tramstop has identical platform numbers, as it can only have one platform
                                        platformTerug = tramStop->getPlatformFrom();
                                    } else {
                                        // TODO Throw error
                                    }
                                }
                            } else {
                                if (!debug)
                                    cerr << "MetroParser: Station with name " << lineNodeElement->Attribute("station")
                                         << " wasn't found" << endl;
                                throw StationNotFoundException();
                            }

                        } else {
                            if (!debug)
                                cerr << "MetroParser: element with name '" << stationElement->Value() << "' not recognized within '" << lineNodeElement->Value() << "'"
                                     << std::endl;
                            throw XMLSyntaxException();
                        }

                        if (platformHeen && platformTerug) {

                            LineNode* node = new LineNode(lineNumber, platformHeen, platformTerug);
                            line->insertNode(node);

                        } else {
                            // Throw error
                        }
                    }
                } else {
                    if (!debug)
                        cerr << "MetroParser: Element with name '" << lineNodeElement->Value() << "' not recognized within '" << lineElement->Value() << "'" << std::endl;
                    throw XMLSyntaxException();
                }
            }

            std::vector<LineNode*> lineAsVector = line->getAsVector();

            if (lineAsVector.size() > 1) {

                for (unsigned int i = 0; i < lineAsVector.size() - 1; i++) {

                    LineNode* currentLineNode = lineAsVector.at(i);
                    LineNode* nextLineNode = lineAsVector.at(i + 1);

                    Platform* sourcePlatform = currentLineNode->getPlatform(TO);
                    Platform* destinationPlatform = nextLineNode->getPlatform(TO);

                    if (!metroNet->hasTrack(sourcePlatform, destinationPlatform)) {
                        addTrackBetweenPlatforms(metroNet, sourcePlatform, destinationPlatform, debug);
                    }
                }

                for (unsigned int i = lineAsVector.size() - 1; i > 0; i--) {

                    LineNode* currentLineNode = lineAsVector.at(i);
                    LineNode* nextLineNode = lineAsVector.at(i - 1);

                    Platform* sourcePlatform = currentLineNode->getPlatform(FROM);
                    Platform* destinationPlatform = nextLineNode->getPlatform(FROM);

                    if (!metroNet->hasTrack(sourcePlatform, destinationPlatform)) {
                        addTrackBetweenPlatforms(metroNet, sourcePlatform, destinationPlatform, debug);
                    }
                }
                metroNet->addLine(line);
            } else {
                if (!debug) std::cerr << "A line cannot have 1 node (occurs at number " << line->getLineNumber() << ")" << std::endl;
                throw SingleNodeLineException();
            }
        }

        void parseTram(MetroNet* metroNet, TiXmlElement* tramElement, bool debug) {

            Line* line = NULL;
            std::string type = "Tram";

            std::string beginStationName;
            Platform* beginPlatform = NULL;

            // Only used if the type is tram
            int lineIndex = -1;
            int amountOfSeats = -1;
            int vehicleNumber = -1;
            if (!tramElement->Attribute("voertuignr")) {
                if (!debug) std::cerr << "Attribute 'voertuignr' not found for tram " << std::endl;
                throw MissingAttributeException();
            } else {
                vehicleNumber = metro_utils::stoi(tramElement->Attribute("voertuignr"));
            }

            if (vehicleNumber < 0) {
                throw NegativeVehicleNumberException();
            }

            double speed = -1;
            double length = -1;

            for (TiXmlElement* tramChildElement = tramElement->FirstChildElement(); tramChildElement != NULL;
                 tramChildElement = tramChildElement->NextSiblingElement()) {
                string elementName = tramChildElement->Value();
                if (elementName == "lijn") {
                    lineIndex = metro_utils::stoi(tramChildElement->GetText());
                    if (lineIndex > 0) {
                        line = metroNet->getLine(lineIndex);
                    }
                } else if (elementName == "type") {
                    type = tramChildElement->GetText();
                } else if (elementName == "length") {
                    length = metro_utils::stod(tramChildElement->GetText());
                }
                if (elementName == "zitplaatsen") {
                    amountOfSeats = metro_utils::stoi(tramChildElement->GetText());
                } else if (elementName == "snelheid") {
                    speed = metro_utils::stod(tramChildElement->GetText());
                } else if (elementName == "beginStation") {
                    beginStationName = tramChildElement->GetText();
                }
            }

            if (!line) {
                if (!debug) std::cerr << " no line '" << lineIndex << "' was parsed from the xml " << std::endl;
                throw LineNotFoundException();
            } else {
                if (!beginStationName.empty()) {

                    LineNode* lineNodeForBeginStation = NULL;

                    std::vector<LineNode*> lineAsVector = line->getAsVector();
                    for (std::vector<LineNode*>::iterator lineNodeIt = lineAsVector.begin(); lineNodeIt != lineAsVector.end(); lineNodeIt++) {
                        if ((*lineNodeIt)->getStation()->getName() == beginStationName) {
                            lineNodeForBeginStation = (*lineNodeIt);
                            break;
                        }
                    }
                    if (!lineNodeForBeginStation) {
                        throw LineNodeNotFoundException();
                    }

                    if (lineNodeForBeginStation) {
                        beginPlatform = lineNodeForBeginStation->getPlatform(TO);
                    } else {
                        if (!debug) std::cerr << " Line Node on line " << line->getLineNumber() << " not found for station " << beginStationName << std::endl;
                        throw LineNodeNotFoundException();
                    }

                } else {
                    if (!debug) std::cerr << "no beginStation name was parsed from the xml " << std::endl;
                    throw StationNotFoundException();
                }
            }

            if (!beginPlatform) {
                if (!debug) std::cerr << "no beginplatform was parsed from the xml " << std::endl;
                throw PlatformNotFoundException();
            }

            Tram* tram = NULL;
            if (type == "PCC") {
                tram = new PCC(line, vehicleNumber, beginPlatform);
            } else if (type == "Albatros") {
                if (line->completelyUnderground()) {
                    tram = new Albatros(line, vehicleNumber, beginPlatform);
                } else {
                    if (!debug) std::cerr << "Creating an albatros which would stop at a (above ground) TramStop. Albatros can't go there" << std::endl;
                    throw TramTypeException();
                }
            } else if (type == "Tram") {
                tram = new Tram(line, beginPlatform, speed, amountOfSeats, vehicleNumber, length, type);
            } else {
                if (!debug) std::cerr << "Metro Parser: unable to recognize tram type" << std::endl;
                throw TramTypeException();
            }

            
            tram->letPassengersIn();
            Statistics::get().updateCurrentDegreeOfOccupancy(tram);
            metroNet->addTram(tram);
            if (!beginPlatform->hasCurrentTram()) {
                beginPlatform->setCurrentTram(tram);
            } else {
                if (!debug) std::cerr << "Another tram cannot be added onto the beginPlatform: it already has a tram and the maximum capacity is 1" << std::endl;
                throw PlatformPropertyException();
            }
        }

        void parseSignal(MetroNet* metroNet, TiXmlElement* signalElement, bool debug) {

            std::string type = "Signal";

            int maxAmountOfTrams = -1;
            // Not implemented yet
            int speedLimitation = -1;

            const char* beginStationName = NULL;
            const char* eindStationName = NULL;

            int beginPlatformNummer = -1;
            int eindPlatformNummer = -1;

            for (TiXmlElement* signalChildElement = signalElement->FirstChildElement(); signalChildElement != NULL;
                 signalChildElement = signalChildElement->NextSiblingElement()) {

                string elementName = signalChildElement->Value();

                if (elementName == "type") {
                    type = signalChildElement->GetText();
                    if (type != "STOP" && type != "SNELHEID") {
                        throw XMLSyntaxException();
                    }
                } else if (type == "STOP" and elementName == "queuesize") {
                    maxAmountOfTrams = metro_utils::stoi(signalChildElement->GetText());
                    if (maxAmountOfTrams < 0) {
                        throw NegativeQueueSizeForTrackException();
                    }
                } else if (type == "SNELHEID") {
                    speedLimitation = metro_utils::stoi(signalChildElement->GetText());
                    if (speedLimitation < 0) {
                        throw NegativeSpeedException();
                    }
                } else if (elementName == "beginPerron") {
                    beginStationName = signalChildElement->FirstChildElement()->GetText();
                    beginPlatformNummer = metro_utils::stoi(signalChildElement->FirstChildElement()->NextSiblingElement()->GetText());
                    if (beginPlatformNummer < 0) {
                        throw NegativePlatformNumberException();
                    }
                } else if (elementName == "eindPerron") {
                    eindStationName = signalChildElement->FirstChildElement()->GetText();
                    eindPlatformNummer = metro_utils::stoi(signalChildElement->FirstChildElement()->NextSiblingElement()->GetText());
                    if (eindPlatformNummer < 0) {
                        throw NegativePlatformNumberException();
                    }
                }
            }

            Station* beginStation = metroNet->getStation(beginStationName);
            Station* eindStation = metroNet->getStation(eindStationName);

            if (!beginStation || !eindStation) {
                throw StationNotFoundException();
            }

            Platform* beginPlatform = NULL;
            Platform* eindPlatform = NULL;

            if (beginStation->getType() == UNDERGROUND) {
                MetroStation* metroStation = (MetroStation*) beginStation;
                beginPlatform = metroStation->getPlatform(beginPlatformNummer);
            } else if (beginStation->getType() == ABOVE_GROUND) {
                TramStop* tramStop = (TramStop*) beginStation;
                if (tramStop->getPlatformTo()->getNumber() == beginPlatformNummer) {
                    beginPlatform = tramStop->getPlatformTo();
                } else {
                    beginPlatform = tramStop->getPlatformFrom();
                }
            }

            if (eindStation->getType() == UNDERGROUND) {
                MetroStation* metroStation = (MetroStation*) eindStation;
                eindPlatform = metroStation->getPlatform(eindPlatformNummer);
            } else if (eindStation->getType() == ABOVE_GROUND) {
                TramStop* tramStop = (TramStop*) eindStation;
                if (tramStop->getPlatformTo()->getNumber() == eindPlatformNummer) {
                    eindPlatform = tramStop->getPlatformTo();
                } else {
                    eindPlatform = tramStop->getPlatformFrom();
                }
            }

            Track* track = metroNet->getTrack(beginPlatform, eindPlatform);

            if (type == "STOP") {
                StopSignal* signal = new StopSignal(track, maxAmountOfTrams);
                track->setStopSignal(signal);
            } else if (type == "SNELHEID") {
                SpeedSignal* signal = new SpeedSignal(track, speedLimitation);
                track->setSpeedSignal(signal);
            }
        }
    }

    MetroNet* parseMetroNetXml(const string& filename, bool debug) {
        /// Opens file in doc
        TiXmlDocument doc;
        if (!doc.LoadFile(filename.c_str())) {
            if (!debug) std::cerr << doc.ErrorDesc() << std::endl;
            throw FileException();
        }

        /// Loads first child element ("MetroNet") in root
        TiXmlElement* root = doc.FirstChildElement();
        if (root == NULL) {
            doc.Clear();
            if (!debug) std::cerr << "Failed to load file: No root element." << std::endl;
            throw FileException();
        }
        /// Get the Metronet name
        string metroNetName = root->Attribute("naam");
        if (metroNetName.empty()) {
            if (!debug) std::cerr << "No name was given for the MetroNet. " << std::endl;
            throw NoNameGivenForMetroNetException();
        }
        MetroNet* metroNet = new MetroNet(metroNetName);

        for (TiXmlElement* rootElement = root->FirstChildElement(); rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {
            if (!strcmp(rootElement->Value(), "STATION")) {
                parseNewStation(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "LIJN")) {
                parseLine(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "TRAM")) {
                parseTram(metroNet, rootElement, debug);
            } else if (!strcmp(rootElement->Value(), "SIGNAAL")) {
                parseSignal(metroNet, rootElement, debug);
            } else {
                if (!debug) std::cerr << "Failed to load file: Unrecognized element '" << rootElement->Value() << "' " << std::endl;
                throw FileException();
            }
        }

        return metroNet;
    }

    const char* FileException::what() const throw() {
        return "Something went wrong with the given file - FileException occurred";
    }

    const char *ExistingTrackException::what() const throw() {
        return "Track already exists - ExistingTrackException occurred";
    }

    const char *EqualSourceAndDestinationOnTrackException::what() const throw() {
        return "Track Destination and Source are equal - EqualSourceAndDestinationOnTrackException occurred";
    }

    const char *NegativePlatformNumberException::what() const throw(){
        return "Platform number cannot be negative - NegativePlatformNumberException occurred";
    }

    const char *NoPlatformsForStationException::what() const throw(){
        return "There is no platform found for this Station - NoPlatformForStationException occurred";
    }

    const char *NoNameGivenForStationException::what() const throw(){
        return "No name was given for a station - NoNameGivenForStationException occurred";
    }

    const char *NoNameGivenForMetroNetException::what() const throw(){
        return "No name was given for the MetroNet - NoNameGivenForMetroNetException occurred";
    }

    const char *ExistingPlatformException::what() const throw(){
        return "Platform already exists - ExistingPlatformException occurred";
    }

    const char *AmountOfPlatformsException::what() const throw(){
        return "Amount of platforms for this station type is not possible - AmountOfPlatformsException occurred";
    }

    const char *StationTypeException::what() const throw(){
        return "Station type does not exist/does not support property - StationTypeException occurred";
    }

    const char *NegativeLineNumberException::what() const throw(){
        return "Line number cannot be negative - NegativeLineNumberException occurred";
    }

    const char *XMLSyntaxException::what() const throw() {
        return "XML Element was not recognized - XMLSyntaxException";
    }

    const char *StationNotFoundException::what() const throw() {
        return "A station which corresponds with the given information was not found - StationNotFoundException occurred";
    }

    const char *SingleNodeLineException::what() const throw() {
        return "A line with 1 node cannot exist - SingleNodeLineException occurred";
    }

    const char *MissingAttributeException::what() const throw() {
        return "Missing attribute for object - MissingAttributeException occurred";
    }

    const char *NegativeVehicleNumberException::what() const throw() {
        return "Vehicle number cannot be negative - NegativeVehicleNumberException occurred";
    }

    const char *LineNodeNotFoundException::what() const throw() {
        return "Line Node which corresponds with the given information was not found - LineNodeNotFoundException occurred";
    }

    const char *LineNotFoundException::what() const throw() {
        return "Line which corresponds with the given information was not found - LineNotFoundException occurred";
    }

    const char *PlatformNotFoundException::what() const throw() {
        return "Platform which corresponds with the given information was not found - PlatformNotFoundException occurred";
    }

    const char *TramTypeException::what() const throw() {
        return "Tram type does not exist/does not support property - TramTypeException occurred";
    }

    const char *PlatformPropertyException::what() const throw(){
        return "A Platform property was violated - PlatformPropertyException occurred";
    }

    const char *NegativeQueueSizeForTrackException::what() const throw() {
        return "A Track queue size cannot be negative - NegativeQueueSizeForTrackException occurred";
    }

    const char *NegativeSpeedException::what() const throw() {
        return "Tramspeed cannot be negative - NegativeSpeedException occurred";
    }
}