//
// Created by rob on 02.06.20.
//

#ifndef PROJECTSOFTWAREENGINEERING_STATISTICS_H
#define PROJECTSOFTWAREENGINEERING_STATISTICS_H

class Tram;

/**
 * @class holding general statistics of the simulation. All MetroNets (multiple allowed, by default: 1) can influence these statistics
 */
class Statistics {

private:

    /**
     * These two values below are used to determine the current occupancy rate.
     * Each time a tram updates the occupancy rate, the amount of seats (occupied & free) of the tram are added to the totalAmountOfSeats variable,
     * As well as the total amount of seats occupied in the tram. Using these values we can determine the current occupancy rate of all trams in the MetroNet
     */
    double m_totalAmountOfOccupancies;
    double m_totalAmountOfSeats;

    /**
     * The total revenue all MetroNets (you can have multiple MetroNets, by default: 1) have gathered (due to Statistics being a singleton class)
     * All trams in the MetroNet contribute the this total revenue
     */
    double m_totalRevenue;

    /**
     * @brief simple constructor
     * (private, singleton) constructs a new statistics class
     */
    Statistics();

public:

    /**
     * @brief simple getter for the singleton
     * @return (if the singleton does not yet exists) a new statistics instance or (if the singleton already exists) a reference to the statistics instance
     */
    static Statistics& get();

    /**
     * @brief simple getter
     * @return the current degree of occupancy. Check the member variable m_currentDegreeOfOccupancy for more information
     */
    double getCurrentDegreeOfOccupancy() const;

    /**
     * @brief simple getter
     * @return the total revenue of all MetroNets in the simulation
     */
    double getTotalRevenue() const;

    /**
     * @brief updates the values that are used to calculate the degreeOfOccupancy
     * @param tram: the tram to update the currentDegreeOfOccupancy with
     */
    void updateCurrentDegreeOfOccupancy(Tram* tram);

    /**
     * @brief adds a new amount of revenue tot the total amount of revenue gathered in this simulation
     * @param revenue: the revenue to add to the total
     */
    void addRevenueToTotal(double revenue);

};


#endif //PROJECTSOFTWAREENGINEERING_STATISTICS_H
