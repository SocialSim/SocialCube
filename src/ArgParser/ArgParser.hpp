#ifndef __ARG_PARSER__
#define __ARG_PARSER__

#include <iostream>
#include <locale>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "cxxopts.hpp"

class ArgParser {
    private:

        // Private member variables

        time_t simulator_startTime;

        time_t simulator_endTime;

        time_t simulator_unitTime;

        bool profile_show;

        bool event_show;

        std::string event_file;

        uint64_t event_buffer;

        bool readFromFile;

        // Private member functions

        void initSocialCubeArgFromCLI(int argc, const char* argv[]);

        void initSocialCubeArgFromFile();

        void parseStartTime(const std::string& t_startTime);

        void parseEndTime(const std::string& t_endTime);

        void parseUnitTime(const std::string& t_unitTime);

        void parseTime(const std::string& str_time, time_t& simulator_time);


    public:
        ArgParser(int argc, const char* argv[]);

        virtual ~ArgParser() final = default;

        time_t getSimulationStartTime();

        time_t getSimulationEndTime();

        time_t getSimulationUnitTime();

        bool getSimulationShowProfileStatus();

        bool getSimulationShowEventStatus();

        uint64_t getSimulationEventBufferSize();

        std::string getSimulationEventFileName();

};

#endif
