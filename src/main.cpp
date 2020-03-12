#include <iostream>
#include <unistd.h>

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"

static bool s_isFinished = false;

void simulateTrams(MetroNet& metroNet) {

    cout << "Simulating trams..." << endl;
    //TODO create a reliable
    while (!s_isFinished) {

        metroNet.updateTramLocations();
        cout << "Updated tram locations " << endl;
        usleep(1000000);
    }
}

int main() {

    cout << "Started up MetroNet..." << endl;
    MetroNet* metroNet = metroParser::parseMetroNetXml("../voorbeeld.xml");
    if (metroNet) {

        metroUtils::printMetroNet(metroNet, "../Summary.metro");
        simulateTrams(*metroNet);

    } else {
        cerr << "MetroNet main: failed to create metronet" << endl;
    }

    cout << "Done running MetroNet..." << endl;

    return 0;
}