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

TEST(InputTest, NegativeInput_emptyFile){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse3.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

TEST(InputTest, NegativeInput_nonExistentFile){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse_nonExistent.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

TEST(InputTest, NegativeInput_falseType){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestFalse4.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

TEST(InputTest, PositiveInput){
    bool failed = false;

    // TODO: This test currently fails because of the way the Albatros Tram type works -> fix + extra tests on these properties

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/voorbeeldTestPositive.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, false);
}

