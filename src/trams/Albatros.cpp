//
// Created by Rob Mandelings on 31/03/2020.
//

#include <clocale>
#include "Albatros.h"

Albatros::Albatros(Line* line, int vehicleNumber, Platform* beginPlatform) :
        Tram(line, beginPlatform, 70, 72, vehicleNumber, 42, "Albatros") {
    // TODO albatros can go above ground, they just won't stop there
    REQUIRE(line->completelyUnderground(), " The line given is invalid; The albatros can only go underground");
}