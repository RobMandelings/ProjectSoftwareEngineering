//
// Created by Rob Mandelings on 2/04/2020.
//

#include "MetroStation.h"

std::vector<Line*> MetroStation::getLines() const {
    return m_lines;
}

Line* MetroStation::getLine(int index) const {
    //TODO REQUIRE index < m_lines.length
    return m_lines.at(index);
}

void MetroStation::addLine(Line* line) {
    Station::addLine(line);
}