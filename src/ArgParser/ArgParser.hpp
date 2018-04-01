#ifndef __ARG_PARSER__
#define __ARG_PARSER__

#include <iostream>
#include <string>
#include "cxxopts.hpp"

class ArgParser {
    private:

        // Private member variables

        uint64_t simulator_startTime;

        uint64_t simulator_currentTime;

        uint64_t simulator_endTime;

        uint64_t simulator_unitTime;

        bool simulator_profile;

        bool readFromFile;

        // Private member functions

        void initSocialCubeArgFromCLI(int argc, const char* argv[]);

        void initSocialCubeArgFromFile();


    public:
        ArgParser(int argc, const char* argv[]);

        virtual ~ArgParser() final = default;

        uint64_t getSimulationStartTime();

        uint64_t getSimulationEndTime();

        uint64_t getSimulationUnitTime();

        uint64_t getSimulationCurrentTime();

        bool getSimulationProfileStatus();

};

#endif
