//
// Created by thibaultpoels on 07/04/2020.
//

#include "Timer.h"
#include "library.h"

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

long Timer::getTimeSinceLastUpdate() {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return static_cast<long>(static_cast<long>(time(NULL))-this->updateTime);
}

void Timer::setUpdateTime() {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    this->updateTime = static_cast<long>(time(NULL));
}
