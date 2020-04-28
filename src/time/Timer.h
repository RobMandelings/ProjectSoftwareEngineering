//
// Created by thibaultpoels on 07/04/2020.
//

#ifndef PROJECTSOFTWAREENGINEERING_TIMER_H
#define PROJECTSOFTWAREENGINEERING_TIMER_H

/**
 * Class used for realistic time
 */

class Timer {
private:
    Timer* _initCheck;

    long timeAtStart;
    long timeAtEnd;

    long updateTime;

    /**
     * @brief simple constructor for Timer
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Timer();

public:

    /**
     * @return the UNIX-time, in milli seconds
     */
    static int getCurrentTimeMillis();

    /**
     * @brief function which returns the singleton for Timer
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    static Timer& get();

    /**
     * @brief function which returns the difference between the time now and the time saved by the member variable updateTime
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    long getUpdateTimePassedMillis() const;

    /**
     * @return the time passed (in milliseconds) since the last update (which is set by the update time)
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    long getTimePassedMillis() const;

    /**
     * @brief simple setter for updateTime
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    void setUpdateTime();

    /**
     * @brief checks if the program should run or stop (depending on a constant set in constants.cpp)
     * @return true if the program should still run
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    bool shouldRun() const;

    /**
     * @brief checks if this object was properly initialized
     */
    bool properlyInitialized() const;

};


#endif //PROJECTSOFTWAREENGINEERING_TIMER_H
