//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

//TEST(OutputTest, PositiveOutput){
//    MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTest.xml");
//    metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
//
//    std::ifstream e("../src/tests/expected_outputs/SummaryTestExample.metro");
//    std::stringstream strExample;
//    strExample << e.rdbuf();
//
//    std::ifstream t("../output/Summary.metro");
//    std::stringstream strTest;
//    strTest << t.rdbuf();
//
//    EXPECT_EQ(strExample.str(), strTest.str());
//}
//
//TEST(EventOutputTest, PositiveOutput){
//    MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTest.xml");
//    metroNet->getLines();
//    //simulation_utils::simulateTrams((*metroNet), 20, true);
//    //TODO: fix
//
//    std::ifstream e("../src/tests/expected_outputs/eventsTestExample.metro");
//    std::stringstream strExample;
//    strExample << e.rdbuf();
//
//    std::ifstream t("../output/events.metro");
//    std::stringstream strTest;
//    strTest << t.rdbuf();
//
//    EXPECT_EQ(strExample.str(),strTest.str());
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}