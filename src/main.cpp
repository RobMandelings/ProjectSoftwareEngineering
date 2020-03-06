#include <iostream>
#include "utils.h"
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

using namespace utils;

int main() {
    MetroNet* metroNet = parseMetroNetXml("../newVoorbeeld.xml");
    const string& name = metroNet->getName();
    cout << name << std::endl;
    Track* track = metroNet->getTrack(12);
    track->traverse();
    Tram* t = metroNet->getTram(12);
    Station* st = t->getBeginNode()->getStation();
    cout << st->getName() << endl;
    return 0;
}