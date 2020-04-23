//
// Created by Rob Mandelings on 6/03/2020.
//

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

// TODO improve metro parser by removing duplicate code (such as the station values that need to be parsed, the error messages which are basically the same
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
                        throw MetroNetParseException();
                    }
                } else {
                    if (!debug)
                        std::cerr << "The destination of the track is equal to the source (station: " << sourcePlatform->getStation()->getName() << ", number: "
                                  << sourcePlatform->getNumber() << ")" << std::endl;
                    throw MetroNetParseException();
                }
            } else {
                if (!debug)
                    std::cerr << "Cannot add track between platforms: the source station and destination station are the same (" << sourcePlatform->getStation()->getName() << ")"
                              << std::endl;
                throw MetroNetParseException();
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
                throw MetroNetParseException();
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
                    stationName = stationChildElement->GetText();
                } else if (childElementName == "type") {
                    stationType = stationChildElement->GetText();
                } else if (childElementName == "perron") {
                    Platform* platform = parseNewPlatform(stationChildElement, debug);
                    platforms.push_back(platform);
                }
            }

            if (platforms.empty()) {
                if (!debug) std::cerr << "There are no platforms found for the current station " << stationName << std::endl;
                throw MetroNetParseException();
            }

            Station* station = NULL;
            if (stationType == "MetroStation") {
                MetroStation* metroStation = new MetroStation();
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); ++it) {

                    if (metroStation->getPlatform((*it)->getNumber()) == NULL) {
                        metroStation->addPlatform(*it);
                    } else {
                        if (!debug) std::cerr << "The platform with number " << (*it)->getNumber() << " already exists in the metrostation" << std::endl;
                        throw MetroNetParseException();
                    }
                }
                station = metroStation;
                // The station of the platform is set to the currentStation
                for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); it++) {
                    (*it)->setStation(station);
                }
            } else if (stationType == "TramStop") {
                if (platforms.size() > 1) {
                    if (!debug) std::cerr << "A tram stap can only have 1 platform. Given: " << platforms.size() << std::endl;
                    throw MetroNetParseException();
                } else {
                    station = new TramStop(platforms.at(0));
                    TramStop* tramStop = (TramStop*) station;
                    tramStop->getPlatformHeen()->setStation(station);
                    tramStop->getPlatformTerug()->setStation(station);
                }
            } else {
                if (!debug) std::cerr << "The type of the station wasn't recognized" << stationType << std::endl;
                throw MetroNetParseException();
            }
            station->setName(stationName);

            metroNet->addStation(station);

        }

        void parseLine(MetroNet* metroNet, TiXmlElement* lineElement, bool debug) {
            Line* line = new Line();
            int lineNumber = metro_utils::stoi(lineElement->Attribute("nr"));
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
                                    throw MetroNetParseException();
                                }
                            }

                            if (station) {
                                station->addLine(line);
                                if (station->getType() == UNDERGROUND) {
                                    MetroStation* metroStation = (MetroStation*) station;
                                    platformHeen = metroStation->getPlatform(platformNumberHeen);
                                    platformTerug = metroStation->getPlatform(platformNumberTerug);
                                } else {
                                    TramStop* tramStop = (TramStop*) station;
                                    if (tramStop->getPlatformHeen()->getNumber() == platformNumberHeen) {
                                        platformHeen = tramStop->getPlatformHeen();
                                        // A tramstop has identical platform numbers, as it can only have one platform
                                        platformTerug = tramStop->getPlatformTerug();
                                    } else {
                                        // TODO Throw error
                                    }
                                }
                            } else {
                                if (!debug)
                                    cerr << "MetroParser: Station with name " << lineNodeElement->Attribute("station")
                                         << " wasn't found" << endl;
                                throw MetroNetParseException();
                            }

                        } else {
                            if (!debug)
                                cerr << "MetroParser: element with name '" << stationElement->Value() << "' not recognized within '" << lineNodeElement->Value() << "'"
                                     << std::endl;
                            throw MetroNetParseException();
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
                    throw MetroNetParseException();
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
                throw MetroNetParseException();
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
            int vechicleNumber = -1;
            if (!tramElement->Attribute("voertuignr")) {
                if (!debug) std::cerr << "Attribute 'voertuignr' not found for tram " << std::endl;
                throw MetroNetParseException();
            } else {
                vechicleNumber = metro_utils::stoi(tramElement->Attribute("voertuignr"));
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
                //TODO what to do if the type is not a default tram but PCC for example? 'zitplaatsen' should not be used in this case
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
                throw MetroNetParseException();
            } else {
                if (!beginStationName.empty()) {

                    LineNode* lineNodeForBeginStation = NULL;

                    std::vector<LineNode*> lineAsVector = line->getAsVector();
                    for (std::vector<LineNode*>::iterator lineNodeIt = lineAsVector.begin(); lineNodeIt <= lineAsVector.end(); lineNodeIt++) {
                        if ((*lineNodeIt)->getStation()->getName() == beginStationName) {
                            lineNodeForBeginStation = (*lineNodeIt);
                            break;
                        }
                    }

                    if (lineNodeForBeginStation) {
                        beginPlatform = lineNodeForBeginStation->getPlatform(TO);
                    } else {
                        if (!debug) std::cerr << " Line Node on line " << line->getLineNumber() << " not found for station " << beginStationName << std::endl;
                        throw MetroNetParseException();
                    }

                } else {
                    if (!debug) std::cerr << "no beginStation name was parsed from the xml " << std::endl;
                    throw MetroNetParseException();
                }
            }

            if (!beginPlatform) {
                if (!debug) std::cerr << " beginplatform was parsed from the xml " << std::endl;
                throw MetroNetParseException();
            }

            Tram* tram = NULL;
            if (type == "PCC") {
                tram = new PCC(line, vechicleNumber, beginPlatform);
            } else if (type == "Albatros") {
                if (line->completelyUnderground()) {
                    tram = new Albatros(line, vechicleNumber, beginPlatform);
                } else {
                    if (!debug) std::cerr << "Creating an albatros which would stop at a (above ground) TramStop. Albatros can't go there" << std::endl;
                    throw MetroNetParseException();
                }
            } else if (type == "Tram") {
                tram = new Tram(line, beginPlatform, speed, amountOfSeats, vechicleNumber, length, type);
            } else {
                if (!debug) std::cerr << "Metro Parser: unable to recognize tram type" << std::endl;
                throw MetroNetParseException();
            }

            metroNet->addTram(tram);
            if (!beginPlatform->hasCurrentTram()) {
                beginPlatform->setCurrentTram(tram);
            } else {
                if (!debug) std::cerr << "Another tram cannot be added onto the beginPlatform: it already has a tram and the maximum capacity is 1" << std::endl;
                throw MetroNetParseException();
            }

            // TODO check if there is a way for the tram to reach all its stations in the line (and back)
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
                } else if (type == "STOP" and elementName == "queuesize") {
                    maxAmountOfTrams = metro_utils::stoi(signalChildElement->GetText());
                } else if (type == "SNELHEID") {
                    speedLimitation = metro_utils::stoi(signalChildElement->GetText());
                } else if (elementName == "beginPerron") {
                    beginStationName = signalChildElement->FirstChildElement()->GetText();
                    beginPlatformNummer = metro_utils::stoi(signalChildElement->FirstChildElement()->NextSiblingElement()->GetText());
                } else if (elementName == "eindPerron") {
                    eindStationName = signalChildElement->FirstChildElement()->GetText();
                    eindPlatformNummer = metro_utils::stoi(signalChildElement->FirstChildElement()->NextSiblingElement()->GetText());
                }
            }

            Station* beginStation = metroNet->getStation(beginStationName);
            Station* eindStation = metroNet->getStation(eindStationName);

            Platform* beginPlatform = NULL;
            Platform* eindPlatform = NULL;

            // TODO improve: one method to get the correct platform

            if (beginStation->getType() == UNDERGROUND) {
                MetroStation* metroStation = (MetroStation*) beginStation;
                beginPlatform = metroStation->getPlatform(beginPlatformNummer);
            } else if (beginStation->getType() == ABOVE_GROUND) {
                TramStop* tramStop = (TramStop*) beginStation;
                if (tramStop->getPlatformHeen()->getNumber() == beginPlatformNummer) {
                    beginPlatform = tramStop->getPlatformHeen();
                } else {
                    beginPlatform = tramStop->getPlatformTerug();
                }
            }

            if (eindStation->getType() == UNDERGROUND) {
                MetroStation* metroStation = (MetroStation*) eindStation;
                eindPlatform = metroStation->getPlatform(eindPlatformNummer);
            } else if (eindStation->getType() == ABOVE_GROUND) {
                TramStop* tramStop = (TramStop*) eindStation;
                if (tramStop->getPlatformHeen()->getNumber() == eindPlatformNummer) {
                    eindPlatform = tramStop->getPlatformHeen();
                } else {
                    eindPlatform = tramStop->getPlatformTerug();
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

    const char* MetroNetParseException::what() const throw() {
        return "A metronet parse exception occurred";
    }

// TODO tram: je moet een gegeven spoor ook meegeven met uw beginstation, tenzij er geen dubbelzinnigheid bestaat
    MetroNet* parseMetroNetXml(const string& filename, bool debug) {
        /// Opens file in doc
        TiXmlDocument doc;
        if (!doc.LoadFile(filename.c_str())) {
            if (!debug) std::cerr << doc.ErrorDesc() << std::endl;
            throw MetroNetParseException();
        }

        /// Loads first child element ("MetroNet") in root
        TiXmlElement* root = doc.FirstChildElement();
        if (root == NULL) {
            doc.Clear();
            if (!debug) std::cerr << "Failed to load file: No root element." << std::endl;
            throw metro_parser::MetroNetParseException();
        }
        //TODO: fix bug with "station=name" (|name| > 1)
        /// Get the Metronet name
        string metroNetName = root->Attribute("naam");
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
                throw MetroNetParseException();
            }
        }

        return metroNet;
    }
}