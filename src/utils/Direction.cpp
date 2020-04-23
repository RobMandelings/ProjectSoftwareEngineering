//
// Created by Rob Mandelings on 14/04/2020.
//

#include "Direction.h"

std::ostream& operator<<(std::ostream& os, Direction& direction) {
    return os << (direction == FROM ? "From" : "To");
}