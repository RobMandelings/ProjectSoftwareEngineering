//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
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
    metro_utils::getGraphicalImpression("../src/tests/test_outputs/SummaryTest.metro", "../src/test/test_outputs/graphicalLines_test1.metro");

    std::ifstream e("../src/test/expected_outputs/graphicalLinesExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("../src/test/test_outputs/graphicalLines_test1.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample.str(), strTest.str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}