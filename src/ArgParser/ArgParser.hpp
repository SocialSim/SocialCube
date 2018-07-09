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

        std::string simulator_center;

        bool profile_show;

        bool event_show;

        std::string event_file;

        std::string proxy_config_file;

        std::string default_file_path;

        uint64_t event_buffer;

        bool readFromFile;

        std::string simulator_timeZone;

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

        std::string getSimulationCenter();

        bool getSimulationShowProfileStatus();

        bool getSimulationShowEventStatus();

        uint64_t getSimulationEventBufferSize();

        std::string getSimulationEventFileName();

        std::string getProxyConfigFileName();

        std::string getDefaultFilePath();

};

#endif
