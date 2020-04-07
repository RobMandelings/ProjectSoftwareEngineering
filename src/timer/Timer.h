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

public:

    /**
     * @brief simple constructor of Timer
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */

    Timer();

    /**
     * @brief function which sleeps for 60 seconds while a tram is waiting in a station
    \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its methods.");
    */

    void stationSleep();

    /**
     * @brief function which sleeps for a certain time in seconds while a tram is between stations
     * @param speed: the trams speed
    \n REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its methods.");
    */

    void driveSleep(int speed);

    bool properlyInitialized() const;

};


#endif //PROJECTSOFTWAREENGINEERING_TIMER_H
