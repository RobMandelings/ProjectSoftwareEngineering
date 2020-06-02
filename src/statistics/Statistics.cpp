//
// Created by rob on 02.06.20.
//

#include "Statistics.h"

#include "Tram.h"
#include "DesignByContract.h"

Statistics::Statistics() :
        m_totalRevenue(0.0) {
    _initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

Statistics& Statistics::get() {
    static Statistics statistics;
    return statistics;
}

double Statistics::getCurrentDegreeOfOccupancy() const {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return m_totalAmountOfOccupancies / (double) m_totalAmountOfSeats;
}

double Statistics::getTotalRevenue() const {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    return m_totalRevenue;
}

void Statistics::updateCurrentDegreeOfOccupancy(Tram* tram) {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    REQUIRE(tram, "Given tram cannot be NULL!");

    m_totalAmountOfOccupancies += tram.getOccupiedSeats();
    m_totalAmountOfSeats += tram->getAmountOfSeats();
}

void Statistics::addRevenueToTotal(double revenue) {
    REQUIRE(this->properlyInitialized(),"Timer must be properly initialized to use its member methods.");
    REQUIRE(revenue >= 0, "The added revenue cannot be negative!");
    double previousRevenue = m_totalRevenue;
    m_totalRevenue += revenue;
    ENSURE(m_totalRevenue == previousRevenue + revenue, "The total revenue didn't increase by the amount of revenue specified!");
}

bool Statistics::properlyInitialized() const {
    return _initCheck == this;
}