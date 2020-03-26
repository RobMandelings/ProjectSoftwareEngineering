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
    MetroNet* metroNet = metro_parser::parseMetroNetXml("../input/voorbeeld.xml");
    if (metroNet) {

        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        simulation_utils::simulateTrams(*metroNet, 3);

    } else {
        cerr << "MetroNet main: failed to create metronet" << endl;
    }

    delete metroNet;

    cout << "Done running MetroNet..." << endl;

    return 0;
}