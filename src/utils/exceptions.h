//
// Created by Rob Mandelings on 26/03/2020.
//

#pragma once

#include <exception>

namespace exceptions {

class MetroNetParseException : public std::exception {

public:
    virtual const char* what() const throw();
};
};