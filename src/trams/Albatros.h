//
// Created by Rob Mandelings on 31/03/2020.
//

#pragma once


#include "Tram.h"

class Albatros : public virtual Tram {

public:

    Albatros(Line* line, int vehicleNumber, Platform* beginPlatform);

    bool canOnlyGoUnderground() const { return true; }

};