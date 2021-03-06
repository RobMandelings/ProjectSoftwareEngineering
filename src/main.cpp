#include <iostream>
#include <time/SimulationTime.h>
#include <utils/constants.h>
#include "library.h"

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "metro_parser.h"
#include "metro_utils.h"
#include "simulation_utils.h"
#include "Timer.h"
#include "FileHandler.h"
#include "SimulationTime.h"

int main() {

    srand(time(0));
    
    MetroNet* metroNet = NULL;

    try {
        metroNet = metro_parser::parseMetroNetXml("../input/voorbeeldComplex.xml");
            std::vector<long> returnTimes;
            simulation_utils::simulateTrams(*metroNet, returnTimes);
        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        metro_utils::getGraphicalImpression("../output/Summary.metro", "../output/graphicalLines.metro");
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}