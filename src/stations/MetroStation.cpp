//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"
#include "lines/Line.h"

std::vector<Line*> MetroStation::getLines() const {
    REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
    return m_lines;
}

Line* MetroStation::getLine(int index) const {
    REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
    REQUIRE((unsigned int)index<m_lines.size()-1,"Index must be smaller than the size of the list of lines.");
    return m_lines.at(index);
}

void MetroStation::addLine(Line* line) {
    REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
    REQUIRE(line!=NULL && line->properlyInitialized(),"Line cannot be NULL.");
    Station::addLine(line);
}