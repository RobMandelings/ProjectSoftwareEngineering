//
// Created by jasper on 12/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metroUtils.h"
#include "metroParser.h"


TEST(OutputTest, PositiveOutput){
    MetroNet* metroNet = metroParser::parseMetroNetXml("tests/voorbeeldTest.xml");
    metroUtils::printMetroNet(metroNet, "tests/SummaryTest.metro");

    std::ifstream e("./expected_outputs/SummaryTestExample.metro");
    std::stringstream strExample;
    strExample << e.rdbuf();

    std::ifstream t("SummaryTest.metro");
    std::stringstream strTest;
    strTest << t.rdbuf();

    EXPECT_EQ(strExample, strTest);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}