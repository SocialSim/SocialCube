#ifndef __ARG_PARSER__
#define __ARG_PARSER__

#include <iostream>
#include <cstdlib>
#include <string>
#include "cxxopts.hpp"

class ArgParser {
    private:

        // Private member variables

        uint64_t simulator_startTime;

        uint64_t simulator_endTime;

        uint64_t simulator_unitTime;

        bool profile_show;

        bool event_show;

        std::string event_file;

        uint64_t event_buffer;

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

        bool getSimulationShowProfileStatus();

        bool getSimulationShowEventStatus();

        uint64_t getSimulationEventBufferSize();

        std::string getSimulationEventFileName();

};

#endif
