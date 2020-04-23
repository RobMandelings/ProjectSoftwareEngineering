//
// Created by Rob Mandelings on 14/04/2020.
//

#pragma once

#include <fstream>

enum Direction {
    TO,
    FROM
};

std::ostream& operator<<(std::ostream& os, Direction& direction);