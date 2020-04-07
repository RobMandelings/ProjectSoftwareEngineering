//
// Created by Rob Mandelings on 31/03/2020.
//

#include "PCC.h"

PCC::PCC(Line* line, Station* beginStation) :
        // TODO what should the length of this PCC be?
        Tram(line, beginStation, 40, 16, 25, "PCC") {}