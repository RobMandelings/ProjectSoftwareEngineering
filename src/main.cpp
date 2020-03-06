#include <iostream>
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "utils/metroParser.h"

int main() {
    MetroNet* metroNet = metroParser::parseMetroNetXml("../newVoorbeeld.xml");
    const string& name = metroNet->getName();
    cout << name << std::endl;
    Track* track = metroNet->getTrack(12);
    track->traverse();
    //Tram* t = metroNet->getTram(12);
    //Station* st = t->getBeginNode()->getStation();
    //cout << st->getName() << endl;
    return 0;
}