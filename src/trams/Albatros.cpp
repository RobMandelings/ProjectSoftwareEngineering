//
// Created by Rob Mandelings on 31/03/2020.
//

#include <clocale>
#include "Albatros.h"

Albatros::Albatros(Line* line, int vehicleNumber, Platform* beginPlatform) :
        Tram(line, beginPlatform, 3500, 72, vehicleNumber, 42, "Albatros") {
}