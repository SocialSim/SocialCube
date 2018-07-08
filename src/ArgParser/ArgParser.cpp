#include "ArgParser.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

ArgParser::ArgParser(int argc, const char* argv[]) {

    initSocialCubeArgFromCLI(argc, argv);

    if(readFromFile)
        initSocialCubeArgFromFile();
}

void ArgParser::initSocialCubeArgFromCLI(int argc, const char* argv[]) {
    try { 
        cxxopts::Options options(argv[0], "Optional Argument for SocialCube");
        options
          .positional_help("[optional args]")
          .show_positional_help();

        options.add_options()
          ("help", "Help")
          ("s, start_time", "Simulation start time", cxxopts::value<string>())
          ("e, end_time", "Simulation end time", cxxopts::value<string>())
          ("t, time_zone", "Simulation time zone", cxxopts::value<string>())
          ("u, unit_time", "Simulation unit time", cxxopts::value<string>())
          ("c, center", "User-centric or repo-centric", cxxopts::value<string>())
          ("event_buffer", "Buffer size of Event Manager", cxxopts::value<uint64_t>())
          ("show_profile", "Show profiling results after finishing simulation")
          ("show_event", "Store all events of simulation")
          ("event_file", "File name for storing events", cxxopts::value<string>())
          ("proxy_config_file", "File name for proxy configuration file", cxxopts::value<string>())
          ("init_file", "Read Configuration from File");

        try 
        { 
            auto result = options.parse(argc, argv);

            if (result.count("help")) { 
                std::cout << options.help({""}) << std::endl;
                exit(0);
            } 
            
            // NOTE: checking for time_zone should always happen before
            // Parsing start time and end time. The reason is that 
            // internally parseTime function will call mktime(), which
            // assumes timezone has already been set.
            if (result.count("time_zone")) { 
                simulator_timeZone = result["time_zone"].as<string>();
                setenv( "TZ", simulator_timeZone.c_str(), 1 );
                tzset();
            } else {
                simulator_timeZone = "UTC";
                setenv( "TZ", simulator_timeZone.c_str(), 1 );
                tzset();
            }

            if (result.count("start_time")) { 
                string startTime = result["start_time"].as<string>();
                parseStartTime(startTime);
            } else {
                simulator_startTime = 0;
            }

            if (result.count("end_time")) { 
                string endTime = result["end_time"].as<string>();
                parseEndTime(endTime);
            } else {
                simulator_endTime = 24 * 3600;
            }

            if (result.count("unit_time")) { 
                string unitTime = result["unit_time"].as<string>();
                parseUnitTime(unitTime);
            } else {
                simulator_unitTime = 3600;
            }

            if (result.count("center")) {
                string center = result["center"].as<string>();
                if (center == "user-centric" or center == "repo-centric") {
                    simulator_center = center;
                } else {
                    std::cout << "unknown centric method: " << center << std::endl;
                    exit(1);
                }
            } else {
                simulator_center = "user-centric";
            }

            if (result.count("event_buffer")) { 
                event_buffer = result["event_buffer"].as<uint64_t>();
            } else {
                event_buffer = 1<<20;
            }

            if (result.count("show_profile")) { 
                profile_show = true;
            } else {
                profile_show = false;
            }

            if (result.count("show_event")) { 
                event_show = true;
            } else {
                event_show = false;
            }

            if (result.count("event_file")) { 
                event_file = result["event_file"].as<string>();
            } else {
                const string socialcubePath = (getenv("SOCIALCUBEPATH"));
                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];

                time (&rawtime);
                timeinfo = localtime(&rawtime);

                strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H:%M:%S",timeinfo);
                std::string str(buffer);
                event_file = socialcubePath + "/events" + str + ".txt";
            }

            if (result.count("proxy_config_file")) {
                proxy_config_file = result["proxy_config_file"].as<string>();
            } else {
                const string socialcubePath = (getenv("SOCIALCUBEPATH"));
                proxy_config_file = socialcubePath + "/ProxyFilePaths.config";
            }

            if (result.count("init_file")) { 
                readFromFile = true;
            } else {
                readFromFile = false;
            }

        } catch (const cxxopts::OptionException& e)
        {
            std::cout << "error parsing options: " << e.what() << std::endl;
            exit(1);
        }

    } 
    catch (std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        exit(2);
    } 

    return; 
}

void ArgParser::initSocialCubeArgFromFile() {
    return;
}

time_t ArgParser::getSimulationStartTime() {
    return simulator_startTime;
}

time_t ArgParser::getSimulationEndTime() {
    return simulator_endTime;
}

time_t ArgParser::getSimulationUnitTime() {
    return simulator_unitTime;
}

std::string ArgParser::getSimulationCenter() {
    return simulator_center;
}

bool ArgParser::getSimulationShowProfileStatus() {
    return profile_show;
}

bool ArgParser::getSimulationShowEventStatus() {
    return event_show;
}
string ArgParser::getSimulationEventFileName() {
    return event_file;
}

string ArgParser::getProxyConfigFileName() {
    return proxy_config_file;
}

uint64_t ArgParser::getSimulationEventBufferSize() {
    return event_buffer;
}

void ArgParser::parseTime(const std::string& str_time, time_t& simulator_time) {
    std::tm t = {};
    std::istringstream ss(str_time);

    if (ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
    {
        simulator_time = std::mktime(&t);
    } else {
        throw; 
    }
}

void ArgParser::parseStartTime(const std::string& t_startTime) {
    parseTime(t_startTime, simulator_startTime);
}

void ArgParser::parseEndTime(const std::string& t_endTime) {
    parseTime(t_endTime, simulator_endTime);
}

void ArgParser::parseUnitTime(const std::string& t_unitTime) {
    if(t_unitTime == "h") {
        simulator_unitTime = 3600;
    } else if(t_unitTime == "d") {
        simulator_unitTime = 3600*24;
    } else {
        throw;
    }
}
