//
// Created by thibaultpoels on 27/02/2020.
//

#include "../TrackNode.h"
#include "metroUtils.h"

int metroUtils::stoi(const string& input) {
        int i;
        istringstream(input) >> i;
        return i;
    }