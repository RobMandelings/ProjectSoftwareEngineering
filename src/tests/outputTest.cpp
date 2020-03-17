//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metroUtils.h"
#include "metroParser.h"
#include "simulationUtils.h"

TEST(OutputTest, PositiveOutput){
    MetroNet* metroNet = metroParser::parseMetroNetXml("tests/voorbeeldTest.xml");
    metroUtils::printMetroNet(metroNet, "../../output/Summary.metro");

    std::ifstream e("./expected_outputs/SummaryTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("SummaryTest.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample, strTest);
}

TEST(EventOutputTest, PositiveOutput){
    MetroNet* metroNet = metroParser::parseMetroNetXml("tests/voorbeeldTest.xml");
    simulation::simulateTrams((*metroNet), 20);

    std::ifstream e("./expected_outputs/SummaryTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("SummaryTest.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}