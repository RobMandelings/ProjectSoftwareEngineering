//
// Created by Rob Mandelings on 31/03/2020.
//

#include <clocale>
#include "Albatros.h"

Albatros::Albatros(int line, LineNode* beginNode) :
        //TODO test albatros: completely underground track
        Tram(line, beginNode, 70, 72, 42, "Albatros") {}