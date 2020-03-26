//
// Created by jasper on 26/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

TEST(InputTest, NegativeInput_lijnNode){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse1.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

TEST(InputTest, NegativeInput_falseAttribute){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse2.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

TEST(InputTest, PositiveInput){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestPositive.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, false);
}

