//
// Created by Rob Mandelings on 2/04/2020.
//

#pragma once

#include "Station.h"
#include "library.h"

class Line;

class MetroStation : public virtual Station {

private:

    std::vector<Line*> m_lines;

public:

    StationType getType() const { return UNDERGROUND; };

    /**
     \n REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
     */
    std::vector<Line*> getLines() const;

    /**
     * @return Line pointer
     *
     \n REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
     \n REQUIRE(index<m_lines.size()-1,"Index must be smaller than the size of the list of lines.");
     */
    Line* getLine(int index) const;

    /**
     \n REQUIRE(this->properlyInitialized(),"MetroStation must be initialized before its member variables are used.");
     \n REQUIRE(line!=NULL && line->properlyInitialized(),"Line cannot be NULL.");
     */
    void addLine(Line* line);

};