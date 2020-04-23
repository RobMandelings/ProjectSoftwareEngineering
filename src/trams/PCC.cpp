//
// Created by Rob Mandelings on 31/03/2020.
//

#include "PCC.h"

PCC::PCC(Line* line, int vehicleNumber, Platform* beginPlatform) :
// TODO what should the length of this PCC be?
        Tram(line, beginPlatform, 400, 16, vehicleNumber, 25, "PCC") {}