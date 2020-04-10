//
// Created by Rob Mandelings on 31/03/2020.
//

#pragma once

#include "Tram.h"

class PCC : public virtual Tram {

public:

    PCC(Line* line, int vehicleNumber, Platform* beginPlatform);

};