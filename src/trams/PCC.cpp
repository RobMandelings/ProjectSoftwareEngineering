//
// Created by Rob Mandelings on 31/03/2020.
//

#include "PCC.h"

PCC::PCC(Line* line, int vehicleNumber, Platform* beginPlatform) :
        Tram(line, beginPlatform, 1000, 16, vehicleNumber, 25, "PCC") {}