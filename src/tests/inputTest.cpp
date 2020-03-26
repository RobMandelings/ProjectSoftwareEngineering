//
// Created by jasper on 26/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

TEST(InputTest, FalseInput){


    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse.xml");
        metro_utils::printMetroNet(metroNet, "../output/SummaryTestFalse.metro");
    }
    catch(metro_parser::MetroNetParseException const& e){
        failed = true;
    };

    EXPECT_EQ(failed, true);
}