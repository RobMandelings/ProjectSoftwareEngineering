//
// Created by Rob Mandelings on 26/03/2020.
//

#include "exceptions.h"

namespace exceptions {
    const char* MetroNetParseException::what() const throw() {
        return "A metronet parse exception occurred";
    }
}