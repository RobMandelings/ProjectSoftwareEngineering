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
        m_ofsteam(outputFilename, std::ofstream::trunc) {
    FileHandler::_initCheck = this;
    ENSURE(this->properlyInitialized(), "Constructor must end ...");
}

std::ofstream& FileHandler::getOfstream() {
    return m_ofsteam;
}

FileHandler::~FileHandler() {
    if (m_ofsteam.is_open()) {
        std::cout << "its open" << std::endl;
    }
    m_ofsteam.close();
    std::cout << "FIleHandler closed" << std::endl;
}
