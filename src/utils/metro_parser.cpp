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

// TODO improve metro parser by removing duplicate code (such as the station values that need to be parsed, the error messages which are basically the same
namespace metro_parser {

    namespace {

//        void addTrackBetweenPlatforms(MetroNet* metroNet, Platform* sourcePlatform, Platform* destinationPlatform, bool debug) {
//
//            if (sourcePlatform != destinationPlatform) {
//                if (!metroNet->trackExists(sourcePlatform, destinationPlatform)) {
//                    Track* track = new Track(sourcePlatform, destinationPlatform);
//                    sourcePlatform->addOutgoingTrack(track);
//                    destinationPlatform->addIncomingTrack(track);
//                    metroNet->addTrack(track);
//                } else {
//                    if (!debug)
//                        std::cerr << "track with source platform 'station " << sourcePlatform->getStation()->getName() << ", number " << sourcePlatform->getNumber() << "'"
//                                  << " and destination platform 'station " << destinationPlatform->getStation()->getName() << ", number " << destinationPlatform->getNumber()
//                                  << "' already exists in the metronet" << std::endl;
//                    throw MetroNetParseException();
//                }
//            } else {
//                if (!debug)
//                    std::cerr << "The destination of the track is equal to the source (station: " << sourcePlatform->getStation()->getName() << ", number: "
//                              << sourcePlatform->getNumber() << ")" << std::endl;
//                throw MetroNetParseException();
//            }
//        }
//
//        Platform* getPlatformFromStationElement(MetroNet* metroNet, TiXmlElement* stationElement, bool debug) {
//
//            Station* station = NULL;
//            std::string stationName;
//            int platformNumber = -1;
//
//            for (TiXmlElement* stationChildElement = stationElement->FirstChildElement();
//                 stationChildElement != NULL; stationChildElement = stationChildElement->NextSiblingElement()) {
//                if (!strcmp(stationChildElement->Value(), "naam")) {
//                    station = metroNet->getStation(stationChildElement->GetText());
//                    stationName = stationChildElement->GetText();
//                } else if (!strcmp(stationChildElement->Value(), "perron")) {
//                    platformNumber = metro_utils::stoi(stationChildElement->GetText());
//                } else {
//                    if (!debug) std::cerr << " unrecognized element '" << stationChildElement->Value() << "' within station" << std::endl;
//                    throw MetroNetParseException();
//                }
//            }
//            if (station) {
//                if (station->getType() == UNDERGROUND) {
//                    MetroStation* metroStation = (MetroStation*) station;
//                    return metroStation->getPlatform(platformNumber, HEEN);
//                } else {
//                    TramStop* tramStop = (TramStop*) station;
//                    if (tramStop->getPlatform(HEEN)->getNumber() == platformNumber) {
//                        return tramStop->getPlatform(HEEN);
//                    }
//                }
//            } else {
//                if (!debug) std::cerr << "station '" << stationName << "' was not found for track" << std::endl;
//                throw MetroNetParseException();
//            }
//
//            if (!debug) std::cerr << "platform '" << platformNumber << "' was not found within station" << std::endl;
//            throw MetroNetParseException();
//        }

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

//        void parseTrack(MetroNet* metroNet, TiXmlElement* trackElement, bool debug) {
//
//            std::vector<Platform*> platformNodes;
//
//            for (TiXmlElement* stationElement = trackElement->FirstChildElement();
//                 stationElement != NULL; stationElement = stationElement->NextSiblingElement()) {
//                if (!strcmp(stationElement->Value(), "station")) {
//
//                    Platform* platformHeen = getPlatformFromStationElement(metroNet, stationElement, debug);
//                    if (platformHeen) {
//                        Platform* platformTerug =
//                                metroNet->getPlatform(platformHeen->getStation()->getName().c_str(), platformHeen->getNumber(), platformHeen->getDirection()) != NULL
//                                ? metroNet->getPlatform(platformHeen->getStation()->getName().c_str(), platformHeen->getNumber(), platformHeen->getDirection())
//                                : new Platform(platformHeen->getStation(), platformHeen->getNumber(), platformHeen->getDirection());
//
//                        platformNodes.push_back(platformHeen);
//                        platformNodes.push_back(platformTerug);
//                    } else {
//                        if (!debug) std::cerr << " no forwards platform from station element found " << std::endl;
//                        throw MetroNetParseException();
//                    }
//                } else {
//                    if (!debug) std::cerr << " the node within track '" << stationElement->Value() << "' is not recognized as station" << std::endl;
//                    throw MetroNetParseException();
//                }
//            }
//
//            if (platformNodes.size() == 4) {
//                Platform* sourcePlatformHeen = platformNodes.at(0);
//                Platform* sourcePlatformTerug = platformNodes.at(1);
//                Platform* destinationPlatformHeen = platformNodes.at(2);
//                Platform* destinationPlatformTerug = platformNodes.at(3);
//                addTrackBetweenPlatforms(metroNet, sourcePlatformHeen, destinationPlatformHeen, debug);
//                addTrackBetweenPlatforms(metroNet, sourcePlatformTerug, destinationPlatformTerug, debug);
//            } else {
//                if (!debug)
//                    std::cerr << "The amount of platforms for a track should be equal to 2. Given: " << platformNodes.size() << std::endl;
//                throw MetroNetParseException();
//            }
//        }

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
            } else if (stationType == "TramStop") {
                if (platforms.size() > 1) {
                    if (!debug) std::cerr << "A tram stap can only have 1 platform. Given: " << platforms.size() << std::endl;
                    throw MetroNetParseException();
                } else {
                    station = new TramStop(platforms.at(0));
                }
            } else {
                if (!debug) std::cerr << "The type of the station wasn't recognized" << stationType << std::endl;
                throw MetroNetParseException();
            }

            // The station of the platform is set to the currentStation
            for (std::vector<Platform*>::iterator it = platforms.begin(); it != platforms.end(); it++) {
                (*it)->setStation(station);
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
            metroNet->addLine(line);
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
                        beginPlatform = lineNodeForBeginStation->getPlatform(HEEN);
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
            } else {
                if (!debug) std::cerr << "Failed to load file: Unrecognized element '" << rootElement->Value() << "' " << std::endl;
                throw MetroNetParseException();
            }
        }

        return metroNet;
    }
}