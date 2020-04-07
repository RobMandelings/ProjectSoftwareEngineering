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

    /**
     * @brief simple constructor of Timer
     \n ENSURE(this->properlyInitialized(),"Constructor must end ...");
     */
    Timer();

public:

    const Timer& get() const;

    bool properlyInitialized() const;

};


#endif //PROJECTSOFTWAREENGINEERING_TIMER_H
