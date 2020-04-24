//
// Created by thibaultpoels on 07/04/2020.
//

#include "library.h"
#include "constants.h"
#include "FileHandler.h"

using namespace constants;

FileHandler& FileHandler::get() {
    static FileHandler fileHandler(constants::EVENTS_OUTPUT_FILE);

    return fileHandler;
}

bool FileHandler::properlyInitialized() const {
    return _initCheck == this;
}

FileHandler::FileHandler(const char* outputFilename) :
        m_ofsteam(NULL) {
    m_ofsteam = new ofstream();
    m_ofsteam->open(outputFilename, std::ofstream::trunc);
    FileHandler::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

ofstream& FileHandler::getOfstream() {
    return *m_ofsteam;
}