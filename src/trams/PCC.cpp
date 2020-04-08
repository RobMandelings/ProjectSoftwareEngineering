//
// Created by Rob Mandelings on 31/03/2020.
//

#include "PCC.h"

PCC::PCC(Line* line, int vehicleNumber, Station* beginStation) :
// TODO what should the length of this PCC be?
        Tram(line, beginStation, NULL, 40, 16, vehicleNumber, 25, "PCC") {}