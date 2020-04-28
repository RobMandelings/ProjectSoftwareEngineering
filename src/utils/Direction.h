//
// Created by Rob Mandelings on 14/04/2020.
//

#pragma once

#include <fstream>

/** Convention to be used by a tram to keep track of its current direction */
enum Direction {
    TO,
    FROM
};

std::ostream& operator<<(std::ostream& os, Direction& direction);