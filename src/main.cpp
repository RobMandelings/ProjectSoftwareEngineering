#include <iostream>
#include "library.h"

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "metro_parser.h"
#include "metro_utils.h"
#include "simulation_utils.h"
#include "Timer.h"
#include "FileHandler.h"

int main() {

    MetroNet* metroNet = NULL;

    try {
        metroNet = metro_parser::parseMetroNetXml("../input/voorbeeldSimpel.xml");

        Timer::get().setUpdateTime();
        simulation_utils::simulateTrams(*metroNet);
        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
//        metro_utils::getGraphicalImpression("../output/Summary.metro", "testImpression.txt");
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        std::cerr << e.what();
        return 1;
    }

    FileHandler::get().getOfstream().close();

    return 0;
}