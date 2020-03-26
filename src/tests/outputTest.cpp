//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metroUtils.h"
#include "metroParser.h"
#include "simulationUtils.h"

TEST(OutputTest, PositiveOutput){
    MetroNet* metroNet = metroParser::parseMetroNetXml("../src/tests/voorbeeldTest.xml");
    metroUtils::printMetroNet(metroNet, "../output/Summary.metro");

    std::ifstream e("../src/tests/expected_outputs/SummaryTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("../output/Summary.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample.str(), strTest.str());
}

TEST(EventOutputTest, PositiveOutput){
    MetroNet* metroNet = metroParser::parseMetroNetXml("../src/tests/voorbeeldTest.xml");
    simulation::simulateTrams((*metroNet), 20, true);

    std::ifstream e("../src/tests/expected_outputs/eventsTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("../output/events.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample.str(),strTest.str());
}

//TEST(InputTest, negativeInput) {
//    MetroNet* metroNet = metroParser::parseMetroNetXml("../src/tests/voorbeeldTestFalse.xml");
//
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}