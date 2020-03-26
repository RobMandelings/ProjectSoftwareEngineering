#include <iostream>
#include <constants.h>
#include "library.h"

#include "MetroNet.h"
#include "Tram.h"
#include "Station.h"
#include "metro_parser.h"
#include "metro_utils.h"
#include "simulation_utils.h"

#define CLOG_MAIN
#include "clog.h"

int initialiseLogger() {
    /* Initialize the logger */
    int r = 0;
    r = clog_init_path(constants::LOGGER_ID, "../logger.txt");
    if (r != 0) {
        fprintf(stderr, "Logger initialization failed.\n");
    }

    /* Set minimum log level to info (default: debug) */
    clog_set_level(constants::LOGGER_ID, CLOG_INFO);

    return r;
}

int main() {

    int retValue = initialiseLogger();

    clog_info(CLOG(constants::LOGGER_ID), "Starting up MetroNet project");

    MetroNet* metroNet = NULL;

    try {
        metroNet  = metro_parser::parseMetroNetXml("../input/voorbeeld.xml");

        metro_utils::printMetroNet(metroNet, "../output/Summary.metro");
        simulation_utils::simulateTrams(*metroNet, 3);
        delete metroNet;
    } catch (const metro_parser::MetroNetParseException& e) {
        clog_info(CLOG(constants::LOGGER_ID), e.what());
    }

    clog_info(CLOG(constants::LOGGER_ID), "Done running MetroNet");

    /* Clean up */
    clog_free(constants::LOGGER_ID);

    return retValue;
}