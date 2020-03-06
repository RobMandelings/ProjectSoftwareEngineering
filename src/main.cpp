#include <iostream>
#include "utils.h"
#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"

using namespace utils;

int main() {
    MetroNet* m = parseMetroNetXml("../newVoorbeeld.xml");
    const string& name = m->getName();
    cout << name << std::endl;
    //Tram* t = m->getTram(12);
    //Station* st = t->getBeginStation();
    //cout << st->getName() << endl;
    return 0;
}