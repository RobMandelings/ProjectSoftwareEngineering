#include <iostream>

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"

int main() {
    MetroNet* metroNet = metroParser::parseMetroNetXml("../voorbeeld.xml");
    metroUtils::printMetroNet(metroNet, "../Summary.metro");

    metroNet->updateTramLocations();
    metroNet->updateTramLocations();
    metroNet->updateTramLocations();
    metroNet->updateTramLocations();
    metroNet->updateTramLocations();
    metroNet->updateTramLocations();
    metroUtils::printMetroNet(metroNet, "../Summary2.metro");

    return 0;
}