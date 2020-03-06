#include <iostream>
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"
#include "utils/metroUtils.h"

int main() {
    MetroNet* metroNet = metroParser::parseMetroNetXml("../newVoorbeeld.xml");
    metroUtils::printMetroNet(metroNet);
    return 0;
}