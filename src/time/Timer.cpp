//
// Created by thibaultpoels on 07/04/2020.
//

#include "Timer.h"
#include "library.h"
#include "constants.h"
#include <cstdlib>
#include <sys/timeb.h>

using namespace constants;

Timer& Timer::get() {
    static Timer timer;

    return timer;
}

/** Found: http://www.cplusplus.com/forum/general/43203/ */
int Timer::getCurrentTimeMillis() {
    timeb tb = {};
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

Timer::Timer() {
    Timer::_initCheck = this;
    timeAtStart = getCurrentTimeMillis();
    timeAtEnd = getCurrentTimeMillis() + (int) (RUNTIME_SECONDS * 1000);
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

long Timer::getUpdateTimePassedMillis() const {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return getCurrentTimeMillis() - updateTime;
}

long Timer::getTimePassedMillis() const {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return getCurrentTimeMillis() - timeAtStart;
}

void Timer::setUpdateTime() {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    this->updateTime = getCurrentTimeMillis();
}

bool Timer::shouldRun() const {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return getCurrentTimeMillis() <= timeAtEnd;
}

bool Timer::properlyInitialized() const {
    return _initCheck == this;
}