//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"

class Line;

class MetroStation : public virtual Station {

private:

    std::vector<Line*> m_lines;

public:

    StationType getType() const {return UNDERGROUND; };

    std::vector<Line*> getLines() const;

    Line* getLine(int index) const;

    void addLine(Line* line);

};