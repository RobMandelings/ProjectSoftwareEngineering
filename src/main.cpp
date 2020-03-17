#include <iostream>
#include "library.h"

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"
#include "simulationUtils.h"

int main() {

    cout << "Started up MetroNet..." << endl;
    MetroNet* metroNet = metroParser::parseMetroNetXml("input/voorbeeld.xml");
    if (metroNet) {

        metroUtils::printMetroNet(metroNet, "output/Summary.metro");
        simulation::simulateTrams(*metroNet, 20);

    } else {
        cerr << "MetroNet main: failed to create metronet" << endl;
    }

    cout << "Done running MetroNet..." << endl;

    return 0;
}