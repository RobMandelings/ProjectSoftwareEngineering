//
// Created by Rob Mandelings on 31/03/2020.
//

#include "PCC.h"

PCC::PCC(int line, LineNode* beginNode) :
        // TODO what should the length of this PCC be?
        Tram(line, beginNode, 40, 16, 25, "PCC") {}