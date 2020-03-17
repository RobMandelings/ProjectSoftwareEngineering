#include <iostream>
#include <unistd.h>

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"

static int s_endTime = 20;

void simulateTrams(MetroNet& metroNet) {

    std::ofstream out("../output/events.metro", std::ofstream::trunc);
    out.close();

    cout << "Simulating trams..." << endl;
    while (s_endTime > 0) {

        metroNet.updateTramLocations();
        cout << "Updated tram locations " << endl;
        s_endTime--;
        usleep(1);
    }
}

int main() {

    cout << "Started up MetroNet..." << endl;
    MetroNet* metroNet = metroParser::parseMetroNetXml("../input/voorbeeld.xml");
    if (metroNet) {

        metroUtils::printMetroNet(metroNet, "../output/Summary.metro");
        simulateTrams(*metroNet);

    } else {
        cerr << "MetroNet main: failed to create metronet" << endl;
    }

    cout << "Done running MetroNet..." << endl;

    return 0;
}