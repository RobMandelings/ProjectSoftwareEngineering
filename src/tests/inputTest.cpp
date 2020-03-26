//
// Created by jasper on 26/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

TEST(InputTest, FalseInput){
<<<<<<< HEAD

    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse.xml");
        metro_utils::printMetroNet(metroNet, "../output/SummaryTestFalse.metro");
    }
    catch(metro_parser::MetroNetParseException const& e){
        failed = true;
    };
=======
    MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse.xml");
    metro_utils::printMetroNet(metroNet, "../output/SummaryTestFalse.metro");

    bool failed = false;

    ofstream out("../output/SummaryTestFalse.metro");
    if(out.fail()){
        failed = true;
    }
>>>>>>> master

    EXPECT_EQ(failed, true);
}