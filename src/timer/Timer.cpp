//
// Created by thibaultpoels on 07/04/2020.
//

#include "Timer.h"
#include "DesignByContract.h"
#include <unistd.h>

void Timer::stationSleep() {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its methods.");
    usleep(60); // 60 seconds sleep
}

void Timer::driveSleep(int speed) {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its methods.");
    int sleepTime = (7200/speed);
    usleep(sleepTime);
}

bool Timer::properlyInitialized() const {
    return _initCheck == this;
}

Timer::Timer() {
    Timer::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}
