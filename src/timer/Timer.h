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

    long runTime;

    long updateTime;

    /**
     * @brief simple constructor for Timer
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Timer();

public:

    /**
     * @brief function which returns the singleton for Timer
     */
    static Timer& get();

    /**
     * @brief function which returns the difference between the time now and the time saved by the member variable updateTime
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    long getTimeSinceLastUpdate();

    /**
     * @brief simple setter for updateTime
     \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
     */
    void setUpdateTime();

    /**
     *
     * @return
     */

    bool programRunTime();

    bool properlyInitialized() const;

};


#endif //PROJECTSOFTWAREENGINEERING_TIMER_H
