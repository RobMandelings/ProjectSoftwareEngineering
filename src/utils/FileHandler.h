//
// Created by thibaultpoels on 07/04/2020.
//

#pragma once

/**
 * Class used for realistic time
 */

#include <fstream>

class FileHandler {
private:

    FileHandler* _initCheck;

    std::ofstream m_ofsteam;

    explicit FileHandler(const char* outputFilename);

public:

    /**
     * @brief function which returns the singleton for Timer
     */
    static FileHandler& get();

    std::ofstream& getOfstream();

    bool properlyInitialized() const;

};