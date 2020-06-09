//
// Created by jasper on 26/03/2020.
//

#include <gtest.h>
#include <fstream>
#include "metro_utils.h"
#include "metro_parser.h"
#include "simulation_utils.h"

/**
 * Wrong station input type
 */
TEST(InputTest, NegativeInput_station_1){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test1.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::StationTypeException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Wrong station input perron (negative input)
 */
TEST(InputTest, NegativeInput_station_2){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test2.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativePlatformNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Station with type tramStop gets 2 perrons
 */
TEST(InputTest, NegativeInput_station_3){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test3.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::AmountOfPlatformsException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Negative line number
 */
TEST(InputTest, NegativeInput_line_1){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test4.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativeLineNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Negative number "heenperron"
 */
TEST(InputTest, NegativeInput_line_2){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test5.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativePlatformNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Negative number "terugperron"
 */
TEST(InputTest, NegativeInput_line_3){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test6.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativePlatformNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Wrong type for signal
 */
TEST(InputTest, NegativeInput_signaal_1){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test7.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::XMLSyntaxException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In Signal negative input in queuesize
 */
TEST(InputTest, NegativeInput_signaal_2){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test8.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativeQueueSizeForTrackException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In signal non existant Station is given in "beginPerron"
 */
TEST(InputTest, NegativeInput_signaal_3){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test9.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::StationNotFoundException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In signal negative perron number in "beginPerron"
 */
TEST(InputTest, NegativeInput_signaal_4){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test10.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativePlatformNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In signal non existant Station in "eindPerron"
 */
TEST(InputTest, NegativeInput_signaal_5){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test11.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::StationNotFoundException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In tram negative input number
 */
TEST(InputTest, NegativeInput_tram_1){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test12.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::NegativeVehicleNumberException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In tram wrong input type
 */
TEST(InputTest, NegativeInput_tram_2){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test13.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::TramTypeException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In tram negative number in "lijn"
 */
TEST(InputTest, NegativeInput_tram_3){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test14.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::LineNotFoundException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * In tram non existant station in "beginStation"
 */
TEST(InputTest, NegativeInput_tram_4){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test15.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::LineNodeNotFoundException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * Empty file as input
 */
TEST(InputTest, NegativeInput_empty){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test16.xml", true);
        // Avoid "not used" warning
        metroNet->getName();
    }
    catch(metro_parser::FileException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * The inputfile Existent
 */
TEST(InputTest, NegativeInput_nonExistent){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_nonExistant.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::FileException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, true);
}

/**
 * positive input should run without any throws
 */
TEST(InputTest, PositiveInput){
    bool failed = false;

    try{
        MetroNet* metroNet = metro_parser::parseMetroNetXml("../src/tests/input_test17.xml", true);
        metroNet->getName();
    }
    catch(metro_parser::MetroNetParseException const& e) {
        failed = true;
    }

    EXPECT_EQ(failed, false);
}
