#include "ArgParser.hpp"

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
          ("s, start_time", "Simulation start time", cxxopts::value<uint64_t>())
          ("e, end_time", "Simulation end time", cxxopts::value<uint64_t>())
          ("u, unit_time", "Simulation unit time", cxxopts::value<uint64_t>())
          ("event_buffer", "Buffer size of Event Manager", cxxopts::value<uint64_t>())
          ("show_profile", "Show profiling results after finishing simulation")
          ("show_event", "Store all events of simulation")
          ("help", "Help")
          ("event_file", "File name for storing events", cxxopts::value<string>())
          ("init_file", "Read Configuration from File");

        try 
        { 
            auto result = options.parse(argc, argv);

            if (result.count("help")) { 
                std::cout << options.help({""}) << std::endl;
                exit(0);
            } 
            if (result.count("start_time")) { 
                simulator_startTime = result["start_time"].as<uint64_t>();
            } else {
                simulator_startTime = 0;
            }

            if (result.count("end_time")) { 
                simulator_endTime = result["end_time"].as<uint64_t>();
            } else {
                simulator_endTime = 24;
            }

            if (result.count("unit_time")) { 
                simulator_unitTime = result["unit_time"].as<uint64_t>();
            } else {
                simulator_unitTime = 1;
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
                event_file = socialcubePath + string("/events.txt");
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

uint64_t ArgParser::getSimulationStartTime() {
    return simulator_startTime;
}

uint64_t ArgParser::getSimulationEndTime() {
    return simulator_endTime;
}

uint64_t ArgParser::getSimulationUnitTime() {
    return simulator_unitTime;
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

uint64_t ArgParser::getSimulationEventBufferSize() {
    return event_buffer;
}
