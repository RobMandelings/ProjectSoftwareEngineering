#include <iostream>
#include <unistd.h>

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"

static bool s_isFinished = false;

void simulateTrams(MetroNet& metroNet) {

    //TODO create a reliable
    while (!s_isFinished) {

        metroNet.updateTramLocations();
        usleep(1000000);
    }
}

int main() {
    MetroNet* metroNet = metroParser::parseMetroNetXml("../newVoorbeeld.xml");
    if (metroNet) {

        metroUtils::printMetroNet(metroNet, "../Summary.metro");
        simulateTrams(*metroNet);

    } else {
        cerr << "MetroNet main: failed to create metronet" << endl;
    }

    return 0;
}