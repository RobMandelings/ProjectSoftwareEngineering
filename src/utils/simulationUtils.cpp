//
// Created by thibaultpoels on 17/03/2020.
//

#include "simulationUtils.h"

namespace simulation{
    void simulateTrams(MetroNet& metroNet, int MAXTIME) {

        std::ofstream out("output/events.metro", std::ofstream::trunc);
        out.close();

        cout << "Simulating trams..." << endl;
        while (MAXTIME > 0) {

            metroNet.updateTramLocations();
            cout << "Updated tram locations " << endl;
            MAXTIME--;
            usleep(1000000);
        }
    }
}
