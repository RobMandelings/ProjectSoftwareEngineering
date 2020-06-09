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
        std::vector<long> returnTimesMillis;
        returnTimesMillis.push_back(1000);
        if (simulation_utils::simulateTrams(*metroNet, returnTimesMillis)) {
            std::cout << "Simulation returned at " << SimulationTime::get().getFormattedTime() << std::endl;
            Timer::get().setUpdateTime();
            usleep(1 / (float) constants::UPDATES_PER_SECOND * 1e6);
            simulation_utils::simulateTrams(*metroNet, returnTimesMillis);
            
            // Write tests...
        } else {
            std::cout << "Simulation ended at " << SimulationTime::get().getFormattedTime() << std::endl;
        }
        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        metro_utils::getGraphicalImpression("../output/Summary.metro", "../output/graphicalLines.metro");
        delete metroNet;
    } catch (const metro_parser::MetroNetException& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}