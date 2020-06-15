//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
#include <time/Timer.h>
#include <utils/constants.h>
#include <time/SimulationTime.h>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

TEST(OutputTest, PositiveOutput){
    MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/output_test1.xml");
    metro_utils::printMetroNet(metroNet, "../src/tests/test_outputs/SummaryTest.metro");

    std::ifstream e("../src/tests/expected_outputs/SummaryTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("../src/tests/test_outputs/SummaryTest.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample.str(), strTest.str());
}

/**
 * Tests if graphical impression is right
 */
TEST(OutputTest, Positive_graphicalImpression){
    MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/output_test1.xml");
    metro_utils::printMetroNet(metroNet, "../src/tests/test_outputs/SummaryTest.metro");
    metro_utils::getGraphicalImpression("../src/tests/test_outputs/SummaryTest.metro", "../src/tests/test_outputs/graphicalLines_test1.metro");

    std::ifstream e("../src/tests/expected_outputs/graphicalLinesExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("../src/tests/test_outputs/graphicalLines_test1.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample.str(), strTest.str());
}

TEST(OutputTest, simulation_run){
    srand(time(0));

    MetroNet* metroNet = NULL;

    try {
        metroNet = metro_parser::parseMetroNetXml("../input/voorbeeldComplex.xml");
        std::vector<long> returnTimesMillis;
        returnTimesMillis.push_back(5000);
        returnTimesMillis.push_back(10000);

        bool simulationPaused;

        do {

            simulationPaused = simulation_utils::simulateTrams(*metroNet, returnTimesMillis, true);

            if (simulationPaused) {
                // TODO write .equal tests
                std::cout << "Simulation returned at " << SimulationTime::get().getFormattedTime() << std::endl;

                Timer::get().setUpdateTime();
                usleep(1 / (float) constants::UPDATES_PER_SECOND * 1e6);
            }
        } while (simulationPaused);
        std::cout << "Simulation ended at " << SimulationTime::get().getFormattedTime() << std::endl;

        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        metro_utils::getGraphicalImpression("../output/Summary.metro", "../output/graphicalLines.metro");
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        std::cerr << e.what();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}