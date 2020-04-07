//
// Created by thibaultpoels on 07/04/2020.
//

#include "Timer.h"
#include "DesignByContract.h"
#include <unistd.h>

const Timer& Timer::get() const {
    static Timer timer;

    return timer;
}

bool Timer::properlyInitialized() const {
    return _initCheck == this;
}

Timer::Timer() {
    Timer::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}
