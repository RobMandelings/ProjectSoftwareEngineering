#include <iostream>
#include "library.h"

#include "MetroNet.h"
#include "trams/Tram.h"
#include "Station.h"
#include "metro_parser.h"
#include "metro_utils.h"
#include "simulation_utils.h"
#include "Timer.h"
int main() {

    MetroNet* metroNet = NULL;

    try {
        metroNet = metro_parser::parseMetroNetXml("../input/voorbeeld.xml");

        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        simulation_utils::simulateTrams(*metroNet, 3);
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}