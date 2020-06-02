//
// Created by rob on 02.06.20.
//

#include "Statistics.h"

#include "Tram.h"
#include "DesignByContract.h"

Statistics::Statistics() :
        m_totalRevenue(0.0) {}

Statistics& Statistics::get() {

    static Statistics statistics;
    return statistics;
}

double Statistics::getCurrentDegreeOfOccupancy() const {
    return m_totalAmountOfOccupancies / m_totalAmountOfSeats;
}

double Statistics::getTotalRevenue() const {
    return m_totalRevenue;
}

void Statistics::updateCurrentDegreeOfOccupancy(Tram* tram) {
    REQUIRE(tram, "Given tram cannot be NULL!");

    m_totalAmountOfOccupancies += tram.getOccupiedSeats();
    m_totalAmountOfSeats += tram->getAmountOfSeats();
}

void Statistics::addRevenueToTotal(double revenue) {
    REQUIRE(revenue >= 0, "The added revenue cannot be negative!");
    m_totalRevenue += revenue;
}