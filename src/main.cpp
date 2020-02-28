#include <iostream>
#include "utils.h"
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

using namespace utils;

int main() {
    MetroNet* m = parseMetroNetXml("../voorbeeld.xml");
    string name = m->getName();
    Tram* t = m->getTram(12);
    Station* st = t->getBeginStation();
    cout << st->getName() << endl;
    return 0;
}