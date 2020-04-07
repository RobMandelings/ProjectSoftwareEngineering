//
// Created by Rob Mandelings on 31/03/2020.
//

#include <clocale>
#include "Albatros.h"

Albatros::Albatros(Line* line, int vehicleNumber, Station* beginStation) :
        Tram(line, beginStation, 70, 72,vehicleNumber, 42, "Albatros") {
    REQUIRE(line->completelyUnderground(), " The line given is invalid; The albatros can only go underground");
}