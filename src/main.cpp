#include <iostream>
#include "library.h"

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "metro_parser.h"
#include "metro_utils.h"
#include "simulation_utils.h"

int main() {

    cout << "Started up MetroNet..." << endl;
    MetroNet* metroNet = NULL;

    try {
        metroNet  = metro_parser::parseMetroNetXml("../input/voorbeeld.xml");

        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        simulation_utils::simulateTrams(*metroNet, 3);
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        std::cout << e.what() << std::endl;
    }

    cout << "Done running MetroNet..." << endl;

    return 0;
}